#!/bin/bash

PROJECT_DIR=$(pwd)
COMPILER_DIR=$PROJECT_DIR/compiler
EXAMPLE_DIR=$COMPILER_DIR/examples
SOURCE_DIR=$COMPILER_DIR/src
LEXER_DIR=$SOURCE_DIR/lexer
PARSER_DIR=$SOURCE_DIR/parser
SEMANTIC_DIR=$SOURCE_DIR/semantic
export PYTHONPATH=$PYTHONPATH:$PROJECT_DIR

cd $PARSER_DIR
read -p "Debug mode? [y/N]: " DEBUG
if [[ $DEBUG =~ ^[Yy]$ ]]; then
    bison -d -Wcounterexamples "$PARSER_DIR/elegant_parser.y"
else
    bison -d "$PARSER_DIR/elegant_parser.y"
fi
cd $LEXER_DIR
flex "$LEXER_DIR/elegant_lexer.l"
cd $PARSER_DIR
gcc -o "$PARSER_DIR/elegant_parser" "$PARSER_DIR/elegant_parser.tab.c" "$LEXER_DIR/lex.yy.c" -lfl -lpython3.10 $(python3.10-config --cflags --ldflags)
"$PARSER_DIR/elegant_parser" "$EXAMPLE_DIR/elegant_example.mepl"
if [[ $DEBUG =~ ^[Yy]$ ]]; then
    nasm -f elf -F dwarf -o "$EXAMPLE_DIR/elegant_example.o" "$EXAMPLE_DIR/elegant_example.asm"
    gcc -m32 -no-pie -g -o "$EXAMPLE_DIR/elegant_example" "$EXAMPLE_DIR/elegant_example.o"
else
    nasm -f elf -o "$EXAMPLE_DIR/elegant_example.o" "$EXAMPLE_DIR/elegant_example.asm"
    gcc -m32 -no-pie -o "$EXAMPLE_DIR/elegant_example" "$EXAMPLE_DIR/elegant_example.o"
fi
"$EXAMPLE_DIR/elegant_example"