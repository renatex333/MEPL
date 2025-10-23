#include "../ast/elegant_ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Code Generator Functions */

CodeGenerator* create_code_generator(const char *filename) {
    CodeGenerator *codegen = (CodeGenerator*)malloc(sizeof(CodeGenerator));
    if (!codegen) {
        fprintf(stderr, "Memory allocation failure for code generator.\n");
        exit(1);
    }
    
    /* Initialize LLVM */
    codegen->context = LLVMContextCreate();
    codegen->module = LLVMModuleCreateWithNameInContext("elegant_module", codegen->context);
    codegen->builder = LLVMCreateBuilderInContext(codegen->context);
    codegen->symbol_table = create_symbol_table();
    codegen->label_counter = 0;
    
    /* Create main function */
    LLVMTypeRef main_func_type = LLVMFunctionType(LLVMInt32TypeInContext(codegen->context), NULL, 0, 0);
    codegen->main_function = LLVMAddFunction(codegen->module, "main", main_func_type);
    
    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(codegen->context, codegen->main_function, "entry");
    LLVMPositionBuilderAtEnd(codegen->builder, entry);
    
    /* Declare printf */
    LLVMTypeRef printf_arg_types[] = { LLVMPointerType(LLVMInt8TypeInContext(codegen->context), 0) };
    LLVMTypeRef printf_type = LLVMFunctionType(LLVMInt32TypeInContext(codegen->context), printf_arg_types, 1, 1);
    codegen->printf_func = LLVMAddFunction(codegen->module, "printf", printf_type);
    
    /* Declare scanf */
    LLVMTypeRef scanf_arg_types[] = { LLVMPointerType(LLVMInt8TypeInContext(codegen->context), 0) };
    LLVMTypeRef scanf_type = LLVMFunctionType(LLVMInt32TypeInContext(codegen->context), scanf_arg_types, 1, 1);
    codegen->scanf_func = LLVMAddFunction(codegen->module, "scanf", scanf_type);
    
    return codegen;
}

static LLVMValueRef create_format_string(CodeGenerator *codegen, const char *format) {
    return LLVMBuildGlobalStringPtr(codegen->builder, format, "format_str");
}

void codegen_evaluate(ASTNode *node, CodeGenerator *codegen, VarType *result_type, LLVMValueRef *result_value) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_CONVERSATION: {
            for (int i = 0; i < node->child_count; i++) {
                codegen_evaluate(node->children[i], codegen, NULL, NULL);
            }
            break;
        }
        
        case NODE_BLOCK: {
            for (int i = 0; i < node->child_count; i++) {
                codegen_evaluate(node->children[i], codegen, NULL, NULL);
            }
            break;
        }
        
        case NODE_INT_VALUE: {
            int value = atoi(node->value);
            if (result_value) *result_value = LLVMConstInt(LLVMInt32TypeInContext(codegen->context), value, 0);
            if (result_type) *result_type = VAR_TYPE_INT;
            break;
        }
        
        case NODE_STRING_VALUE: {
            if (result_value) *result_value = LLVMBuildGlobalStringPtr(codegen->builder, node->value, "str");
            if (result_type) *result_type = VAR_TYPE_STRING;
            break;
        }
        
        case NODE_IDENTIFIER: {
            SymbolTableEntry *entry = symbol_table_get(codegen->symbol_table, node->value);
            LLVMValueRef loaded_value = LLVMBuildLoad2(codegen->builder, 
                                          entry->type == VAR_TYPE_INT ? 
                                              LLVMInt32TypeInContext(codegen->context) : 
                                              LLVMPointerType(LLVMInt8TypeInContext(codegen->context), 0),
                                          entry->alloca_inst, 
                                          "load_var");
            if (result_value) *result_value = loaded_value;
            if (result_type) *result_type = entry->type;
            break;
        }
        
        case NODE_DECLARATION: {
            const char *var_name = node->children[0]->value;
            VarType var_type = strcmp(node->value, "INT") == 0 ? VAR_TYPE_INT : VAR_TYPE_STRING;
            
            LLVMTypeRef alloca_type = var_type == VAR_TYPE_INT ? 
                LLVMInt32TypeInContext(codegen->context) : 
                LLVMArrayType(LLVMInt8TypeInContext(codegen->context), MAX_STR_SIZE);
            
            LLVMValueRef alloca = LLVMBuildAlloca(codegen->builder, alloca_type, var_name);
            symbol_table_add(codegen->symbol_table, var_name, var_type, alloca);
            
            /* Initialize to zero/empty */
            if (var_type == VAR_TYPE_INT) {
                LLVMBuildStore(codegen->builder, LLVMConstInt(LLVMInt32TypeInContext(codegen->context), 0, 0), alloca);
            } else {
                /* Initialize string to empty */
                LLVMValueRef zero = LLVMConstInt(LLVMInt8TypeInContext(codegen->context), 0, 0);
                for (int i = 0; i < MAX_STR_SIZE; i++) {
                    LLVMValueRef indices[] = { 
                        LLVMConstInt(LLVMInt32TypeInContext(codegen->context), 0, 0),
                        LLVMConstInt(LLVMInt32TypeInContext(codegen->context), i, 0)
                    };
                    LLVMValueRef ptr = LLVMBuildGEP2(codegen->builder, alloca_type, alloca, indices, 2, "");
                    LLVMBuildStore(codegen->builder, zero, ptr);
                }
            }
            
            /* Handle initial value if provided */
            if (node->child_count > 1) {
                VarType init_type;
                LLVMValueRef init_value;
                codegen_evaluate(node->children[1], codegen, &init_type, &init_value);
                
                if (init_type != var_type) {
                    fprintf(stderr, "Elegant Misalignment: Type mismatch in declaration.\n");
                    exit(1);
                }
                
                LLVMBuildStore(codegen->builder, init_value, alloca);
            }
            break;
        }
        
        case NODE_ASSIGNMENT: {
            VarType value_type;
            LLVMValueRef value;
            codegen_evaluate(node->children[1], codegen, &value_type, &value);
            
            SymbolTableEntry *entry = symbol_table_get(codegen->symbol_table, node->children[0]->value);
            
            if (entry->type != value_type) {
                fprintf(stderr, "Elegant Misalignment: Type mismatch in assignment.\n");
                exit(1);
            }
            
            LLVMBuildStore(codegen->builder, value, entry->alloca_inst);
            break;
        }
        
        case NODE_BINARY_OP: {
            VarType left_type, right_type;
            LLVMValueRef left_val, right_val;
            
            codegen_evaluate(node->children[0], codegen, &left_type, &left_val);
            codegen_evaluate(node->children[1], codegen, &right_type, &right_val);
            
            if (left_type == VAR_TYPE_INT && right_type == VAR_TYPE_INT) {
                LLVMValueRef bin_result = NULL;
                if (strcmp(node->value, "added to") == 0) {
                    bin_result = LLVMBuildAdd(codegen->builder, left_val, right_val, "add");
                } else if (strcmp(node->value, "subtracted from") == 0) {
                    bin_result = LLVMBuildSub(codegen->builder, right_val, left_val, "sub");
                } else if (strcmp(node->value, "multiplied by") == 0) {
                    bin_result = LLVMBuildMul(codegen->builder, left_val, right_val, "mul");
                } else if (strcmp(node->value, "divided by") == 0) {
                    bin_result = LLVMBuildSDiv(codegen->builder, right_val, left_val, "div");
                } else if (strcmp(node->value, "equates to") == 0) {
                    LLVMValueRef cmp = LLVMBuildICmp(codegen->builder, LLVMIntEQ, left_val, right_val, "cmp");
                    bin_result = LLVMBuildZExt(codegen->builder, cmp, LLVMInt32TypeInContext(codegen->context), "zext");
                } else if (strcmp(node->value, "differs from") == 0) {
                    LLVMValueRef cmp = LLVMBuildICmp(codegen->builder, LLVMIntNE, left_val, right_val, "cmp");
                    bin_result = LLVMBuildZExt(codegen->builder, cmp, LLVMInt32TypeInContext(codegen->context), "zext");
                } else if (strcmp(node->value, "exceeds") == 0) {
                    LLVMValueRef cmp = LLVMBuildICmp(codegen->builder, LLVMIntSGT, left_val, right_val, "cmp");
                    bin_result = LLVMBuildZExt(codegen->builder, cmp, LLVMInt32TypeInContext(codegen->context), "zext");
                } else if (strcmp(node->value, "is less than") == 0) {
                    LLVMValueRef cmp = LLVMBuildICmp(codegen->builder, LLVMIntSLT, left_val, right_val, "cmp");
                    bin_result = LLVMBuildZExt(codegen->builder, cmp, LLVMInt32TypeInContext(codegen->context), "zext");
                } else if (strcmp(node->value, "or") == 0) {
                    bin_result = LLVMBuildOr(codegen->builder, left_val, right_val, "or");
                } else if (strcmp(node->value, "and") == 0) {
                    bin_result = LLVMBuildAnd(codegen->builder, left_val, right_val, "and");
                }
                if (result_value) *result_value = bin_result;
                if (result_type) *result_type = VAR_TYPE_INT;
            } else {
                fprintf(stderr, "String operations not fully implemented.\n");
                if (result_value) *result_value = LLVMConstInt(LLVMInt32TypeInContext(codegen->context), 0, 0);
                if (result_type) *result_type = VAR_TYPE_INT;
            }
            break;
        }
        
        case NODE_UNARY_OP: {
            VarType operand_type;
            LLVMValueRef operand_val;
            codegen_evaluate(node->children[0], codegen, &operand_type, &operand_val);
            
            if (operand_type != VAR_TYPE_INT) {
                fprintf(stderr, "Unary operations only supported on integers.\n");
                exit(1);
            }
            
            LLVMValueRef unary_result;
            if (strcmp(node->value, "positively") == 0) {
                unary_result = operand_val;
            } else if (strcmp(node->value, "negatively") == 0) {
                unary_result = LLVMBuildNeg(codegen->builder, operand_val, "neg");
            } else if (strcmp(node->value, "not") == 0) {
                LLVMValueRef zero = LLVMConstInt(LLVMInt32TypeInContext(codegen->context), 0, 0);
                LLVMValueRef cmp = LLVMBuildICmp(codegen->builder, LLVMIntEQ, operand_val, zero, "not");
                unary_result = LLVMBuildZExt(codegen->builder, cmp, LLVMInt32TypeInContext(codegen->context), "zext");
            }
            if (result_value) *result_value = unary_result;
            if (result_type) *result_type = VAR_TYPE_INT;
            break;
        }
        
        case NODE_DISPLAY: {
            VarType display_type;
            LLVMValueRef display_val;
            codegen_evaluate(node->children[0], codegen, &display_type, &display_val);
            
            LLVMValueRef format_str;
            if (display_type == VAR_TYPE_INT) {
                format_str = create_format_string(codegen, "%d\n");
                LLVMValueRef args[] = { format_str, display_val };
                LLVMTypeRef printf_arg_types[] = { LLVMPointerType(LLVMInt8TypeInContext(codegen->context), 0) };
                LLVMTypeRef printf_type = LLVMFunctionType(LLVMInt32TypeInContext(codegen->context), printf_arg_types, 1, 1);
                LLVMBuildCall2(codegen->builder, printf_type, codegen->printf_func, args, 2, "");
            } else {
                format_str = create_format_string(codegen, "%s\n");
                LLVMValueRef args[] = { format_str, display_val };
                LLVMTypeRef printf_arg_types[] = { LLVMPointerType(LLVMInt8TypeInContext(codegen->context), 0) };
                LLVMTypeRef printf_type = LLVMFunctionType(LLVMInt32TypeInContext(codegen->context), printf_arg_types, 1, 1);
                LLVMBuildCall2(codegen->builder, printf_type, codegen->printf_func, args, 2, "");
            }
            break;
        }
        
        case NODE_SOLICITATION: {
            SymbolTableEntry *entry = symbol_table_get(codegen->symbol_table, node->children[0]->value);
            
            LLVMValueRef format_str;
            if (entry->type == VAR_TYPE_INT) {
                format_str = create_format_string(codegen, "%d");
                LLVMValueRef args[] = { format_str, entry->alloca_inst };
                LLVMTypeRef scanf_arg_types[] = { LLVMPointerType(LLVMInt8TypeInContext(codegen->context), 0) };
                LLVMTypeRef scanf_type = LLVMFunctionType(LLVMInt32TypeInContext(codegen->context), scanf_arg_types, 1, 1);
                LLVMBuildCall2(codegen->builder, scanf_type, codegen->scanf_func, args, 2, "");
            } else {
                format_str = create_format_string(codegen, "%s");
                LLVMValueRef args[] = { format_str, entry->alloca_inst };
                LLVMTypeRef scanf_arg_types[] = { LLVMPointerType(LLVMInt8TypeInContext(codegen->context), 0) };
                LLVMTypeRef scanf_type = LLVMFunctionType(LLVMInt32TypeInContext(codegen->context), scanf_arg_types, 1, 1);
                LLVMBuildCall2(codegen->builder, scanf_type, codegen->scanf_func, args, 2, "");
            }
            break;
        }
        
        case NODE_CONDITIONAL: {
            VarType cond_type;
            LLVMValueRef cond_val;
            codegen_evaluate(node->children[0], codegen, &cond_type, &cond_val);
            
            if (cond_type != VAR_TYPE_INT) {
                fprintf(stderr, "Condition must be integer type.\n");
                exit(1);
            }
            
            LLVMValueRef zero = LLVMConstInt(LLVMInt32TypeInContext(codegen->context), 0, 0);
            LLVMValueRef cond = LLVMBuildICmp(codegen->builder, LLVMIntNE, cond_val, zero, "cond");
            
            LLVMBasicBlockRef then_block = LLVMAppendBasicBlockInContext(codegen->context, codegen->main_function, "then");
            LLVMBasicBlockRef else_block = node->child_count > 2 ? 
                LLVMAppendBasicBlockInContext(codegen->context, codegen->main_function, "else") : NULL;
            LLVMBasicBlockRef merge_block = LLVMAppendBasicBlockInContext(codegen->context, codegen->main_function, "merge");
            
            if (else_block) {
                LLVMBuildCondBr(codegen->builder, cond, then_block, else_block);
            } else {
                LLVMBuildCondBr(codegen->builder, cond, then_block, merge_block);
            }
            
            LLVMPositionBuilderAtEnd(codegen->builder, then_block);
            codegen_evaluate(node->children[1], codegen, NULL, NULL);
            LLVMBuildBr(codegen->builder, merge_block);
            
            if (else_block) {
                LLVMPositionBuilderAtEnd(codegen->builder, else_block);
                codegen_evaluate(node->children[2], codegen, NULL, NULL);
                LLVMBuildBr(codegen->builder, merge_block);
            }
            
            LLVMPositionBuilderAtEnd(codegen->builder, merge_block);
            break;
        }
        
        case NODE_LOOP: {
            LLVMBasicBlockRef loop_cond = LLVMAppendBasicBlockInContext(codegen->context, codegen->main_function, "loop_cond");
            LLVMBasicBlockRef loop_body = LLVMAppendBasicBlockInContext(codegen->context, codegen->main_function, "loop_body");
            LLVMBasicBlockRef loop_exit = LLVMAppendBasicBlockInContext(codegen->context, codegen->main_function, "loop_exit");
            
            LLVMBuildBr(codegen->builder, loop_cond);
            
            LLVMPositionBuilderAtEnd(codegen->builder, loop_cond);
            VarType cond_type;
            LLVMValueRef cond_val;
            codegen_evaluate(node->children[0], codegen, &cond_type, &cond_val);
            
            LLVMValueRef zero = LLVMConstInt(LLVMInt32TypeInContext(codegen->context), 0, 0);
            LLVMValueRef cond = LLVMBuildICmp(codegen->builder, LLVMIntNE, cond_val, zero, "loop_cond");
            LLVMBuildCondBr(codegen->builder, cond, loop_body, loop_exit);
            
            LLVMPositionBuilderAtEnd(codegen->builder, loop_body);
            codegen_evaluate(node->children[1], codegen, NULL, NULL);
            LLVMBuildBr(codegen->builder, loop_cond);
            
            LLVMPositionBuilderAtEnd(codegen->builder, loop_exit);
            break;
        }
        
        case NODE_NOP:
            break;
    }
}

void codegen_finalize(CodeGenerator *codegen, const char *output_file) {
    /* Return 0 from main */
    LLVMBuildRet(codegen->builder, LLVMConstInt(LLVMInt32TypeInContext(codegen->context), 0, 0));
    
    /* Verify module */
    char *error = NULL;
    LLVMVerifyModule(codegen->module, LLVMAbortProcessAction, &error);
    LLVMDisposeMessage(error);
    
    /* Write bitcode to file */
    char bc_file[512];
    snprintf(bc_file, sizeof(bc_file), "%s.bc", output_file);
    if (LLVMWriteBitcodeToFile(codegen->module, bc_file) != 0) {
        fprintf(stderr, "Error writing bitcode file.\n");
        exit(1);
    }
    
    printf("LLVM IR bitcode written to: %s\n", bc_file);
}

void free_code_generator(CodeGenerator *codegen) {
    if (codegen) {
        free_symbol_table(codegen->symbol_table);
        LLVMDisposeBuilder(codegen->builder);
        LLVMDisposeModule(codegen->module);
        LLVMContextDispose(codegen->context);
        free(codegen);
    }
}
