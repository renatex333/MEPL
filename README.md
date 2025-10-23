# MEPL

MEPL - The Most Elegant Programming Language 🎩🍸

"Black Tie Programming: Where Code Meets Class"

MEPL is not just another programming language, **it's an experience in elegance**. With simplicity at its core, every line of code you write in MEPL feels like poetry. We've trimmed the excess, focusing only on the essential features, and have draped them in the most sophisticated syntax ever conceived. Welcome to a world where programming isn't just about solving problems—it's about doing so with grace and style.

Key Features:

    Sophisticated Syntax: Code that reads like a black-tie invitation.
    Essentials Only: No bloat. Just pure, elegant functionality.
    Dressed to Impress: With tooling and libraries that reflect our commitment to elegance.

Dive into MEPL and discover the unparalleled pleasure of "Black Tie Programming."

## EBNF (Extended Backus-Naur Form)

### Grammar Definitions

```
# Grammatical Elements:
#
# * Strings with double quotes (") denote keywords.
# * Upper case names (NAME) denote tokens in the Grammar/Tokens file.
# * First character upper case names (Name) denote rule names.
#
# Grammar Syntax:
#
# Rule Name = expression
#   The rule is defined by the expression. 
# expression 1, expression 2
#   Match expression 1, then match expression 2.
# expression 1 | expression 2
#   Match expression 1 or expression 2.
# ( expression )
#   Match expression.
# [ expression ]
#   Optionally match expression.
# { expression }
#   Match zero or more occurrences of expression.
#
```

### Rule Definitions

```
Elegant Conversation    = Greeting, { Sentence } ;
Greeting                = "Greetings", "." ; 
Sentence                = ( Declare | Assign | Conditional | Loop | Solicitation | Display) ;
Declare                 = "I introduce", Identifier, "as", 
                          ("an integer" | "a string"), 
                          [ "carrying the value of", Boolean Expression ], "." ;
Assign                  = "Please, let", Identifier, 
                          "be given the value of", Boolean Expression, "." ;
Conditional             = "In the event that", Boolean Expression, "holds true:", 
                          Block, [ "Otherwise:", Block ] ;
Loop                    = "Whilst", Boolean Expression, "holds true:", Block ;
Solicitation            = "May I solicit a brand new value for", Identifier, "." ;
Display                 = "Kindly display the following expression:", Boolean Expression, "." ;
Block                   = "Firstly,", { Sentence }, "... as a conclusion to the matter", "." ;
Boolean Expression      = Boolean Clause, { "or", Boolean Clause } ;
Boolean Clause          = Relational Expression, { "and", Relational Expression } ;
Relational Expression   = Expression, { ("equates to" | "differs from" | "exceeds" | "is less than"), Expression } ;
Expression              = Term, { ("added to" | "subtracted from" | "concatenated with" ), Term } ;
Term                    = Factor, { ("multiplied by" | "divided by"), Factor } ;
Factor                  = Number | String | Identifier | (("positively" | "negatively" | "not"), Factor) ;
Identifier              = Letter, { Letter | Digit | "_" } ;
Number                  = Digit, { Digit } ;
String                  = `"`, { λ | Letter | Digit | Special Character }, `"` ;
Letter                  = ( a | ... | z | A | ... | Z ) ;
Digit                   = ( 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 ) ;
Special Character       = ( @ | # | $ | % | ^ | & | * | ( | ) | _ | + | { | } | [ | ] | | | \ | : 
                          | ; | ' | < | > | , | . | ? | / | ! | ? | - | ~ ) ;
```

## Current Constraints and Forthcoming Refinements

### Elegantly Crafted for Specific Environments

At present, the MEPL language is meticulously tailored for the Linux Operating System, exclusively flourishing within the realms of x86-64 architectures. This precise crafting ensures a harmonious and refined interaction with the said environment, providing an exquisite coding experience.

### Current Limitations in String Operations

In the current stage of MEPL's evolution, certain string operations — specifically, concatenation, equivalence, and difference — remain a work in artful progress. Attempts to employ these functionalities may lead to a momentary lapse in the otherwise smooth execution of elegantly composed code. It is a deliberate design decision that arithmetic operations (sum, subtraction, multiplication, division) and boolean operations (such as 'or' and 'and') between strings will not be implemented, as they do not align with the intrinsic elegance upheld in MEPL. The operations of "solicitations" (the term for scanning) and "displays" (printing) with strings, however, are functioning with utmost grace and efficiency, as intended.

## Instructions

MEPL now offers two compiler backends: a modern **LLVM backend** (recommended) and the original **Python backend**.

### LLVM Backend (Recommended)

The LLVM backend provides better performance, optimization, and doesn't require Python runtime dependencies.

#### Compiling with LLVM

1. Craft Your Code: Pen down your MEPL code in a file with the **.mepl** extension.
2. Compile: To transmute your written code into an executable form, simply run in your terminal:

        ./elegant_compiler_llvm <filename>

Replacing `<filename>` with the name of your **.mepl** file or the relative path to it.

#### Rebuilding the LLVM Compiler

To rebuild the LLVM-based compiler after making changes:

    ./elegant_builder_llvm

**Dependencies**: LLVM development libraries, Clang, Flex, Bison

    sudo apt install llvm-dev clang flex bison

### Python Backend (Legacy)

The original implementation using Python and NASM assembly generation.

#### Compiling with Python Backend

1. Craft Your Code: Pen down your MEPL code in a file with the **.mepl** extension.
2. Compile: To transmute your written code into an executable form, simply run in your terminal:

        ./elegant_compiler <filename>

Replacing `<filename>` with the name of your **.mepl** file or the relative path to it.

#### Rebuilding the Python Compiler

In the event of making alterations to the foundational elements of MEPL - the lexer, parser, semantic analyzer, or code generator - a reconstruction of the compiler is essential. This ensures that your changes are effectively integrated. To rebuild the compiler execute in your terminal:

    ./elegant_builder

This step ensures that any modifications you have graciously added to these core components are reflected in the subsequent compilations.

**Dependencies**: GCC, NASM, Flex, Bison, Python >=3.10

### Quick Reference to Shell Scripts

Should there arise a need to elegantly wrap the shell scripts in a binary format following any modification, execute in your terminal:

    shc -o elegant_builder -f compiler/src/scripts/builder.sh 
    shc -o elegant_compiler -f compiler/src/scripts/compiler.sh

## References

Aaron Myles Landwehr. (2012). [Flex/Bison Tutorial](https://www.capsl.udel.edu/courses/cpeg421/2012/slides/Tutorial-Flex_Bison.pdf).

Joe "begriffs" Nelson. (2021). [Practical parsing with Flex and Bison](https://begriffs.com/posts/2021-11-28-practical-parsing.html). 

Loren Segal. (2009). [Writing Your Own Toy Compiler Using Flex, Bison and LLVM](https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/). 

Wilfred Hughes. (2014). [Baby Steps to a C Compiler](https://www.wilfred.me.uk/blog/2014/08/27/baby-steps-to-a-c-compiler/).

Continuum Analytics. (2012). [LLVMPY](https://www.llvmpy.org/).

Python. (2023). [Full Grammar specification](https://docs.python.org/3/reference/grammar.html).

IME-USP. (1999). [The Netwide Assembler: NASM](https://www.ime.usp.br/~reverbel/mac211-99/asm/nasm_doc/nasmdoca.html).