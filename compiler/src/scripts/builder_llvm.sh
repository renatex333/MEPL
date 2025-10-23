#!/bin/bash

PROJECT_DIR=$(pwd)
COMPILER_DIR=$PROJECT_DIR/compiler
SOURCE_DIR=$COMPILER_DIR/src
LEXER_DIR=$SOURCE_DIR/lexer
PARSER_DIR=$SOURCE_DIR/parser
AST_DIR=$SOURCE_DIR/ast
CODEGEN_DIR=$SOURCE_DIR/codegen

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}Building MEPL Compiler with LLVM backend...${NC}"

# Check for LLVM
echo -n "Checking if llvm-config is installed... "
if command -v llvm-config &> /dev/null; then
    echo -e "llvm-config ${GREEN}is installed${NC}."
    LLVM_CFLAGS=$(llvm-config --cflags)
    LLVM_LDFLAGS=$(llvm-config --ldflags --libs core executionengine mcjit native bitwriter --system-libs)
else
    echo -e "Error: llvm-config ${RED}is not installed${NC}."
    echo -e "${GREEN}Install LLVM${NC}: ${BLUE}sudo apt-get install llvm-dev${NC}"
    exit 1
fi

cd $PARSER_DIR
read -p "Build in debug mode? [y/N]: " DEBUG
if [[ $DEBUG =~ ^[Yy]$ ]]; then
    echo -e "${YELLOW}Building in debug mode...${NC}"
    bison -d -Wcounterexamples "$PARSER_DIR/elegant_parser_llvm.y"
else
    bison -d "$PARSER_DIR/elegant_parser_llvm.y"
fi

if [ $? -ne 0 ]; then
    echo -e "${RED}Bison failed!${NC}"
    exit 1
fi

cd $LEXER_DIR
flex "$LEXER_DIR/elegant_lexer.l"

if [ $? -ne 0 ]; then
    echo -e "${RED}Flex failed!${NC}"
    exit 1
fi

# Compile AST implementation
echo -e "${BLUE}Compiling AST module...${NC}"
gcc -c -o "$AST_DIR/elegant_ast.o" "$AST_DIR/elegant_ast.c" $LLVM_CFLAGS

if [ $? -ne 0 ]; then
    echo -e "${RED}AST compilation failed!${NC}"
    exit 1
fi

# Compile code generator
echo -e "${BLUE}Compiling code generator module...${NC}"
gcc -c -o "$CODEGEN_DIR/elegant_codegen_llvm.o" "$CODEGEN_DIR/elegant_codegen_llvm.c" $LLVM_CFLAGS

if [ $? -ne 0 ]; then
    echo -e "${RED}Code generator compilation failed!${NC}"
    exit 1
fi

# Link everything
echo -e "${BLUE}Linking compiler...${NC}"
cd $PARSER_DIR
gcc -o "$PARSER_DIR/elegant_parser_llvm" \
    "$PARSER_DIR/elegant_parser_llvm.tab.c" \
    "$LEXER_DIR/lex.yy.c" \
    "$AST_DIR/elegant_ast.o" \
    "$CODEGEN_DIR/elegant_codegen_llvm.o" \
    -lfl \
    $LLVM_CFLAGS \
    $LLVM_LDFLAGS

if [ $? -ne 0 ]; then
    echo -e "${RED}Linking failed!${NC}"
    exit 1
fi

echo -e "${GREEN}Build successful!${NC}"
echo -e "Compiler binary: ${BLUE}$PARSER_DIR/elegant_parser_llvm${NC}"
