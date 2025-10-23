# MEPL AST Module (LLVM Backend)

This directory contains the Abstract Syntax Tree (AST) implementation for the LLVM backend of the MEPL compiler.

## Files

### `elegant_ast.h`
Header file defining all AST-related structures and function prototypes:
- **AST Node Types**: Enumeration of all node types (declarations, operators, control flow, etc.)
- **Data Structures**: AST nodes, symbol table entries, code generator context
- **Function Declarations**: Creation, manipulation, and destruction of AST components

### `elegant_ast.c`
Implementation of AST functionality:
- **Node Management**: Creating and freeing AST nodes
- **Symbol Table**: Adding variables, retrieving types and locations
- **Memory Safety**: Proper allocation and deallocation

## Usage

These modules are compiled as part of the LLVM backend build process:

```bash
gcc -c elegant_ast.c $(llvm-config --cflags) -o elegant_ast.o
```

They are then linked with the parser and code generator to create the complete compiler.

## Key Structures

### ASTNode
Represents a node in the abstract syntax tree:
```c
typedef struct ASTNode {
    NodeType type;                    // Type of node
    char *value;                      // Associated value (identifier, number, etc.)
    struct ASTNode *children[10];     // Child nodes
    int child_count;                  // Number of children
    int index;                        // Unique identifier
} ASTNode;
```

### SymbolTable
Manages variable declarations and their properties:
```c
typedef struct SymbolTable {
    SymbolTableEntry entries[256];    // Variable entries
    int count;                        // Number of variables
} SymbolTable;
```

### CodeGenerator
LLVM code generation context:
```c
typedef struct CodeGenerator {
    LLVMModuleRef module;             // LLVM module
    LLVMBuilderRef builder;           // IR builder
    LLVMContextRef context;           // LLVM context
    LLVMValueRef main_function;       // Main function
    SymbolTable *symbol_table;        // Variable tracking
} CodeGenerator;
```

## Design Principles

1. **Simplicity**: Straightforward C structures, no complex inheritance
2. **Safety**: Bounds checking and error messages for all operations
3. **LLVM Integration**: Structures designed to work seamlessly with LLVM C API
4. **Memory Management**: Explicit allocation and deallocation to prevent leaks

## Error Handling

All functions perform validation and exit with descriptive error messages:
- Undeclared variable access → Exit with identifier name
- Symbol table overflow → Exit with capacity message
- Memory allocation failure → Exit immediately

## Extending

To add new AST node types:
1. Add entry to `NodeType` enum in `.h` file
2. Handle new type in `codegen_evaluate()` function
3. Create nodes with `create_ast_node()` in parser
4. Add appropriate children with `add_child()`

## Constants

- `MAX_STR_SIZE`: Maximum string length (64 bytes)
- `MAX_CHILDREN`: Maximum children per node (10)
- `MAX_VARIABLES`: Maximum variables in symbol table (256)

These can be adjusted based on requirements.
