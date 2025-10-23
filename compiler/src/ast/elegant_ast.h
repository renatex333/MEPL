#ifndef ELEGANT_AST_H
#define ELEGANT_AST_H

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

#define MAX_STR_SIZE 64
#define MAX_CHILDREN 10
#define MAX_VARIABLES 256

typedef enum {
    VAR_TYPE_INT,
    VAR_TYPE_STRING
} VarType;

typedef enum {
    NODE_CONVERSATION,
    NODE_DECLARATION,
    NODE_ASSIGNMENT,
    NODE_IDENTIFIER,
    NODE_INT_VALUE,
    NODE_STRING_VALUE,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_DISPLAY,
    NODE_SOLICITATION,
    NODE_CONDITIONAL,
    NODE_LOOP,
    NODE_BLOCK,
    NODE_NOP
} NodeType;

typedef struct SymbolTableEntry {
    char name[256];
    VarType type;
    LLVMValueRef alloca_inst;
} SymbolTableEntry;

typedef struct SymbolTable {
    SymbolTableEntry entries[MAX_VARIABLES];
    int count;
} SymbolTable;

typedef struct ASTNode {
    NodeType type;
    char *value;
    struct ASTNode *children[MAX_CHILDREN];
    int child_count;
    int index;
} ASTNode;

typedef struct CodeGenerator {
    LLVMModuleRef module;
    LLVMBuilderRef builder;
    LLVMContextRef context;
    LLVMValueRef main_function;
    LLVMValueRef printf_func;
    LLVMValueRef scanf_func;
    SymbolTable *symbol_table;
    int label_counter;
} CodeGenerator;

/* AST Node creation functions */
ASTNode* create_ast_node(NodeType type, const char *value);
void add_child(ASTNode *parent, ASTNode *child);
void free_ast_node(ASTNode *node);

/* Symbol Table functions */
SymbolTable* create_symbol_table(void);
void symbol_table_add(SymbolTable *table, const char *name, VarType type, LLVMValueRef alloca);
SymbolTableEntry* symbol_table_get(SymbolTable *table, const char *name);
void free_symbol_table(SymbolTable *table);

/* Code Generator functions */
CodeGenerator* create_code_generator(const char *filename);
void codegen_evaluate(ASTNode *node, CodeGenerator *codegen, VarType *result_type, LLVMValueRef *result_value);
void codegen_finalize(CodeGenerator *codegen, const char *output_file);
void free_code_generator(CodeGenerator *codegen);

#endif /* ELEGANT_AST_H */
