#include "elegant_ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int node_index_counter = 0;

/* AST Node Functions */

ASTNode* create_ast_node(NodeType type, const char *value) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failure for AST node.\n");
        exit(1);
    }
    
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->child_count = 0;
    node->index = node_index_counter++;
    
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    
    return node;
}

void add_child(ASTNode *parent, ASTNode *child) {
    if (parent->child_count >= MAX_CHILDREN) {
        fprintf(stderr, "Exceeded maximum children for AST node.\n");
        exit(1);
    }
    parent->children[parent->child_count++] = child;
}

void free_ast_node(ASTNode *node) {
    if (!node) return;
    
    if (node->value) {
        free(node->value);
    }
    
    for (int i = 0; i < node->child_count; i++) {
        free_ast_node(node->children[i]);
    }
    
    free(node);
}

/* Symbol Table Functions */

SymbolTable* create_symbol_table(void) {
    SymbolTable *table = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (!table) {
        fprintf(stderr, "Memory allocation failure for symbol table.\n");
        exit(1);
    }
    table->count = 0;
    return table;
}

void symbol_table_add(SymbolTable *table, const char *name, VarType type, LLVMValueRef alloca) {
    if (table->count >= MAX_VARIABLES) {
        fprintf(stderr, "Symbol table capacity exceeded.\n");
        exit(1);
    }
    
    /* Check for redeclaration */
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->entries[i].name, name) == 0) {
            fprintf(stderr, "Declaration Redundancy: The identifier '%s' has been previously declared.\n", name);
            exit(1);
        }
    }
    
    SymbolTableEntry *entry = &table->entries[table->count++];
    strncpy(entry->name, name, 255);
    entry->name[255] = '\0';
    entry->type = type;
    entry->alloca_inst = alloca;
}

SymbolTableEntry* symbol_table_get(SymbolTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->entries[i].name, name) == 0) {
            return &table->entries[i];
        }
    }
    
    fprintf(stderr, "Undeclared Identifier Alert: The identifier '%s' appears to be absent from the declaration scope.\n", name);
    exit(1);
}

void free_symbol_table(SymbolTable *table) {
    if (table) {
        free(table);
    }
}
