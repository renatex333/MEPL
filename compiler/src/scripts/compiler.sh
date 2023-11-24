#!/bin/bash

PROJECT_DIR=$(pwd)
COMPILER_DIR=$PROJECT_DIR/compiler
SOURCE_DIR=$COMPILER_DIR/src
PARSER_DIR=$SOURCE_DIR/parser
export PYTHONPATH=$PYTHONPATH:$PROJECT_DIR

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

command_exists() {
    type "$1" &> /dev/null ;
}

MISSING_DEPENDENCIES=0
echo -n "Checking if gcc is installed... "
if command_exists gcc; then
    echo -e "gcc ${GREEN}is installed${NC}."
else
    echo -e "Error: gcc ${RED}is not installed${NC}. ${GREEN}Download gcc${NC} from: ${BLUE}https://gcc.gnu.org/${NC}"
    MISSING_DEPENDENCIES=1
fi

echo -n "Checking if nasm is installed... "
if command_exists nasm; then
    echo -e "nasm ${GREEN}is installed${NC}."
else
    echo -e "Error: nasm ${RED}is not installed${NC}. ${GREEN}Download nasm${NC} from: ${BLUE}https://www.nasm.us/${NC}"
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
ASSEMBLY_EXTENSION="asm"
OBJECT_EXTENSION="o"
MEPL_EXTENSION="mepl"

if [[ $ORIGINAL_EXTENSION != $MEPL_EXTENSION ]]; then
    echo -e "${RED}Error:${NC} File extension must be ${BLUE}.$MEPL_EXTENSION${NC}."
    exit 1
fi

read -p "Compile in debug mode? [y/N]: " DEBUG
"$PARSER_DIR/elegant_parser" "$PROJECT_DIR/$ORIGINAL_FILEPATH"

if [ $? -eq 1 ]; then
    echo -e "${RED}Error:${NC} Parsing failed."
    exit 1
fi

if [[ $DEBUG =~ ^[Yy]$ ]]; then
    nasm -f elf -F dwarf -o "${BASE_FILENAME}.${OBJECT_EXTENSION}" "${BASE_FILENAME}.${ASSEMBLY_EXTENSION}"
    gcc -m32 -no-pie -g -o "${BASE_FILENAME}" "${BASE_FILENAME}.${OBJECT_EXTENSION}"
else
    nasm -f elf -o "${BASE_FILENAME}.${OBJECT_EXTENSION}" "${BASE_FILENAME}.${ASSEMBLY_EXTENSION}"
    gcc -m32 -no-pie -o "${BASE_FILENAME}" "${BASE_FILENAME}.${OBJECT_EXTENSION}"
fi
rm "${BASE_FILENAME}.${ASSEMBLY_EXTENSION}"
rm "${BASE_FILENAME}.${OBJECT_EXTENSION}"

echo -e "${GREEN}Compilation successful.${NC}"
echo -e "Run program with: ${BLUE}./${BASE_FILENAME}${NC}"