#!/bin/bash

PROJECT_DIR=$(pwd)
COMPILER_DIR=$PROJECT_DIR/compiler
SOURCE_DIR=$COMPILER_DIR/src
PARSER_DIR=$SOURCE_DIR/parser

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

command_exists() {
    type "$1" &> /dev/null ;
}

MISSING_DEPENDENCIES=0
echo -n "Checking if clang is installed... "
if command_exists clang; then
    echo -e "clang ${GREEN}is installed${NC}."
else
    echo -e "Error: clang ${RED}is not installed${NC}. ${GREEN}Install clang${NC}: ${BLUE}sudo apt-get install clang${NC}"
    MISSING_DEPENDENCIES=1
fi

echo -n "Checking if llc is installed... "
if command_exists llc; then
    echo -e "llc ${GREEN}is installed${NC}."
else
    echo -e "Error: llc ${RED}is not installed${NC}. ${GREEN}Install LLVM tools${NC}: ${BLUE}sudo apt-get install llvm${NC}"
    MISSING_DEPENDENCIES=1
fi

if [[ $MISSING_DEPENDENCIES -eq 1 ]]; then
    echo -e "${RED}Missing dependencies. Exiting.${NC}"
    exit 1
fi

if [ "$#" -ne 1 ]; then
    echo -e "${RED}Correct usage:${NC} $0 <filename>"
    exit 1
fi

ORIGINAL_FILEPATH="$1"
BASE_FILENAME="${ORIGINAL_FILEPATH%.*}"
ORIGINAL_EXTENSION="${ORIGINAL_FILEPATH##*.}"
BITCODE_EXTENSION="bc"
ASSEMBLY_EXTENSION="s"
OBJECT_EXTENSION="o"
MEPL_EXTENSION="mepl"

if [[ $ORIGINAL_EXTENSION != $MEPL_EXTENSION ]]; then
    echo -e "${RED}Error:${NC} File extension must be ${BLUE}.$MEPL_EXTENSION${NC}."
    exit 1
fi

read -p "Compile in debug mode? [y/N]: " DEBUG

echo -e "${BLUE}Parsing MEPL source...${NC}"
"$PARSER_DIR/elegant_parser_llvm" "$PROJECT_DIR/$ORIGINAL_FILEPATH"

if [ $? -eq 1 ]; then
    echo -e "${RED}Error:${NC} Parsing failed."
    exit 1
fi

echo -e "${BLUE}Compiling LLVM bitcode to native code...${NC}"

# Convert LLVM bitcode to assembly
llc -filetype=obj -O2 -Oz "${BASE_FILENAME}.${BITCODE_EXTENSION}" -o "${BASE_FILENAME}.${ASSEMBLY_EXTENSION}"

if [ $? -ne 0 ]; then
    echo -e "${RED}Error:${NC} LLVM compilation failed."
    exit 1
fi

# Assemble and link
if [[ $DEBUG =~ ^[Yy]$ ]]; then
    clang -g -no-pie -o "${BASE_FILENAME}" "${BASE_FILENAME}.${ASSEMBLY_EXTENSION}"
else
    clang -no-pie -o "${BASE_FILENAME}" "${BASE_FILENAME}.${ASSEMBLY_EXTENSION}"
fi

if [ $? -ne 0 ]; then
    echo -e "${RED}Error:${NC} Linking failed."
    exit 1
fi

# Cleanup intermediate files
rm "${BASE_FILENAME}.${BITCODE_EXTENSION}"
rm "${BASE_FILENAME}.${ASSEMBLY_EXTENSION}"

echo -e "${GREEN}Compilation successful.${NC}"
echo -e "Run program with: ${BLUE}./${BASE_FILENAME}${NC}"
