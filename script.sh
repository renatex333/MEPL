#!/bin/bash

PROJECT_DIR=$(pwd)
COMPILER_DIR=$PROJECT_DIR/compiler
EXAMPLE_DIR=$COMPILER_DIR/examples
SOURCE_DIR=$COMPILER_DIR/src
LEXER_DIR=$SOURCE_DIR/lexer
PARSER_DIR=$SOURCE_DIR/parser
SEMANTIC_DIR=$SOURCE_DIR/semantic

# rm "$PARSER_DIR/elegant_parser.tab.c" "$PARSER_DIR/elegant_parser.tab.h" "$LEXER_DIR/lex.yy.c" "$PARSER_DIR/elegant_parser"

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
gcc -o "$PARSER_DIR/elegant_parser" "$PARSER_DIR/elegant_parser.tab.c" "$LEXER_DIR/lex.yy.c" -lfl
"$PARSER_DIR/elegant_parser" < "$EXAMPLE_DIR/elegant_example.mepl"