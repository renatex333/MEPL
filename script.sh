#!/bin/bash

# Delete previous files
rm elegant_parser.tab.c elegant_parser.tab.h lex.yy.c elegant_parser

# Run commands
read -p "Debug mode? (y/n): " debug
if [ $debug = "y" ]; then
    bison -d -Wcounterexamples elegant_parser.y
    flex elegant_lexer.l
    gcc -o elegant_parser elegant_parser.tab.c lex.yy.c -lfl
    ./elegant_parser < elegant_example.mepl
    exit 0
fi
bison -d elegant_parser.y
flex elegant_lexer.l

gcc -o elegant_parser elegant_parser.tab.c lex.yy.c -lfl

./elegant_parser < elegant_example.mepl