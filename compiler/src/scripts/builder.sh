#!/bin/bash

PROJECT_DIR=$(pwd)
COMPILER_DIR=$PROJECT_DIR/compiler
EXAMPLE_DIR=$COMPILER_DIR/examples
SOURCE_DIR=$COMPILER_DIR/src
LEXER_DIR=$SOURCE_DIR/lexer
PARSER_DIR=$SOURCE_DIR/parser
export PYTHONPATH=$PYTHONPATH:$PROJECT_DIR

cd $PARSER_DIR
read -p "Build in debug mode? [y/N]: " DEBUG
if [[ $DEBUG =~ ^[Yy]$ ]]; then
    bison -d -Wcounterexamples "$PARSER_DIR/elegant_parser.y"
else
    bison -d "$PARSER_DIR/elegant_parser.y"
fi
cd $LEXER_DIR
flex "$LEXER_DIR/elegant_lexer.l"
cd $PARSER_DIR
gcc -o "$PARSER_DIR/elegant_parser" "$PARSER_DIR/elegant_parser.tab.c" "$LEXER_DIR/lex.yy.c" -lfl -lpython3.10 $(python3.10-config --cflags --ldflags)