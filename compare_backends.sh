#!/bin/bash

# MEPL Backend Comparison Demo
# This script demonstrates the differences between Python and LLVM backends

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

echo -e "${CYAN}╔════════════════════════════════════════════════════════╗${NC}"
echo -e "${CYAN}║     MEPL Compiler Backend Comparison Demo             ║${NC}"
echo -e "${CYAN}╚════════════════════════════════════════════════════════╝${NC}"
echo ""

# Check if test file exists
TEST_FILE="compiler/examples/simple_and_elegant.mepl"
if [ ! -f "$TEST_FILE" ]; then
    echo -e "${RED}Test file not found: $TEST_FILE${NC}"
    exit 1
fi

echo -e "${BLUE}Test Program:${NC}"
echo -e "${YELLOW}──────────────────────────────────────────────────────${NC}"
cat "$TEST_FILE"
echo -e "${YELLOW}──────────────────────────────────────────────────────${NC}"
echo ""

# Function to check if command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Check Python backend dependencies
echo -e "${BLUE}Checking Python Backend Dependencies...${NC}"
PYTHON_OK=true
if ! command_exists gcc; then
    echo -e "${RED}✗ gcc not found${NC}"
    PYTHON_OK=false
else
    echo -e "${GREEN}✓ gcc found${NC}"
fi

if ! command_exists nasm; then
    echo -e "${RED}✗ nasm not found${NC}"
    PYTHON_OK=false
else
    echo -e "${GREEN}✓ nasm found${NC}"
fi

if ! command_exists python3; then
    echo -e "${RED}✗ python3 not found${NC}"
    PYTHON_OK=false
else
    echo -e "${GREEN}✓ python3 found${NC}"
fi

# Check LLVM backend dependencies
echo ""
echo -e "${BLUE}Checking LLVM Backend Dependencies...${NC}"
LLVM_OK=true
if ! command_exists llvm-config; then
    echo -e "${RED}✗ llvm-config not found${NC}"
    LLVM_OK=false
else
    echo -e "${GREEN}✓ llvm-config found (version: $(llvm-config --version))${NC}"
fi

if ! command_exists clang; then
    echo -e "${RED}✗ clang not found${NC}"
    LLVM_OK=false
else
    echo -e "${GREEN}✓ clang found${NC}"
fi

if ! command_exists llc; then
    echo -e "${RED}✗ llc not found${NC}"
    LLVM_OK=false
else
    echo -e "${GREEN}✓ llc found${NC}"
fi

echo ""
echo -e "${CYAN}════════════════════════════════════════════════════════${NC}"

# Test Python Backend
if [ "$PYTHON_OK" = true ]; then
    echo ""
    echo -e "${BLUE}Testing Python Backend...${NC}"
    echo -e "${YELLOW}──────────────────────────────────────────────────────${NC}"
    
    echo -e "${CYAN}Building compiler...${NC}"
    echo | ./elegant_builder > /dev/null 2>&1

    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✓ Build successful${NC}"
        
        echo -e "${CYAN}Compiling test program...${NC}"
        START_TIME=$(date +%s%3N) # Use milliseconds for better compatibility
        echo | ./elegant_compiler "$TEST_FILE" > /dev/null 2>&1
        END_TIME=$(date +%s%3N)
        COMPILE_TIME=$((END_TIME - START_TIME))
        
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}✓ Compilation successful (${COMPILE_TIME}ms)${NC}"
            
            echo -e "${CYAN}Running program...${NC}"
            OUTPUT=$(./compiler/examples/simple_and_elegant 2>&1)
            echo -e "${GREEN}Output:${NC}"
            echo "$OUTPUT"
            
            # Check output file size
            SIZE=$(stat -c%s ./compiler/examples/simple_and_elegant 2>/dev/null)
            echo -e "${CYAN}Executable size: ${SIZE} bytes${NC}"
        else
            echo -e "${RED}✗ Compilation failed${NC}"
        fi
    else
        echo -e "${RED}✗ Build failed${NC}"
    fi
else
    echo -e "${YELLOW}⊘ Python backend dependencies not met, skipping tests${NC}"
fi

# Test LLVM Backend
if [ "$LLVM_OK" = true ]; then
    echo ""
    echo -e "${BLUE}Testing LLVM Backend...${NC}"
    echo -e "${YELLOW}──────────────────────────────────────────────────────${NC}"
    
    echo -e "${CYAN}Building compiler...${NC}"
    echo | ./elegant_builder_llvm > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✓ Build successful${NC}"
        
        echo -e "${CYAN}Compiling test program...${NC}"
        START_TIME=$(date +%s%3N) # Use milliseconds for better compatibility
        echo | ./elegant_compiler_llvm "$TEST_FILE" > /dev/null 2>&1
        END_TIME=$(date +%s%3N)
        COMPILE_TIME=$((END_TIME - START_TIME))
        
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}✓ Compilation successful (${COMPILE_TIME}ms)${NC}"
            
            echo -e "${CYAN}Running program...${NC}"
            OUTPUT=$(./compiler/examples/simple_and_elegant 2>&1)
            echo -e "${GREEN}Output:${NC}"
            echo "$OUTPUT"
            
            # Check output file size
            SIZE=$(stat -c%s ./compiler/examples/simple_and_elegant 2>/dev/null)
            echo -e "${CYAN}Executable size: ${SIZE} bytes${NC}"
        else
            echo -e "${RED}✗ Compilation failed${NC}"
        fi
    else
        echo -e "${RED}✗ Build failed${NC}"
    fi
else
    echo -e "${YELLOW}⊘ LLVM backend dependencies not met, skipping tests${NC}"
fi

echo ""
echo -e "${CYAN}════════════════════════════════════════════════════════${NC}"