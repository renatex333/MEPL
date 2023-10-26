# MEPL

🎩 MEPL - The Most Elegant Programming Language 🍸

"Black Tie Programming: Where Code Meets Class"

MEPL is not just another programming language, **it's an experience in elegance**. With simplicity at its core, every line of code you write in MEPL feels like poetry. We've trimmed the excess, focusing only on the essential features, and have draped them in the most sophisticated syntax ever conceived. Welcome to a world where programming isn't just about solving problems—it's about doing so with grace and style.

🔹 Key Features:

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
ELEGANT CONVERSATION    = GREETINGS, { SENTENCE } ;
GREETING                = "Greetings", "." ; 
SENTENCE                = ( λ | DECLARE | ASSIGN | CONDITIONAL | LOOP ) ;
DECLARE                 = "I introduce", IDENTIFIER, "as", 
                          ("an integer" | "a string"), 
                          [ "carrying the value of", BOOLEAN EXPRESSION ], "." ;
ASSIGN                  = "Please, let", IDENTIFIER, 
                          "be given the value of", BOOLEAN EXPRESSION, "." ;
CONDITIONAL             = "In the event that", BOOLEAN EXPRESSION, "holds true:", 
                          BLOCK, [ "Otherwise:", BLOCK ], "." ;
LOOP                    = "Whilst", BOOLEAN EXPRESSION, "holds true:", BLOCK, "." ;
BLOCK                   = "Firstly", { SENTENCE }, "... as a conclusion to the matter" ;
BOOLEAN EXPRESSION      = BOOLEAN CLAUSE, { "or", BOOLEAN CLAUSE } ;
BOOLEAN CLAUSE          = RELATIONAL EXPRESSION, { "and", RELATIONAL EXPRESSION } ;
RELATIONAL EXPRESSION   = EXPRESSION, { ("equates to" | "exceeds" | "is less than"), EXPRESSION } ;
EXPRESSION              = TERM, { ("added to" | "subtracted by" | "concatenated with"), TERM } ;
TERM                    = FACTOR, { ("multiplied by" | "divided by"), FACTOR } ;
FACTOR                  = NUMBER | STRING | IDENTIFIER | (("positively" | "negatively" | "not"), FACTOR) ;
IDENTIFIER              = LETTER, { LETTER | DIGIT | "_" } ;
NUMBER                  = DIGIT, { DIGIT } ;
STRING                  = `"`, { λ | LETTER | DIGIT }, `"` ;
LETTER                  = ( a | ... | z | A | ... | Z ) ;
DIGIT                   = ( 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 ) ;
```

## References

Aaron Myles Landwehr. (2012). [Flex/Bison Tutorial](https://www.capsl.udel.edu/courses/cpeg421/2012/slides/Tutorial-Flex_Bison.pdf).

Joe "begriffs" Nelson. (2021). [Practical parsing with Flex and Bison](https://begriffs.com/posts/2021-11-28-practical-parsing.html). 

Loren Segal. (2009). [Writing Your Own Toy Compiler Using Flex, Bison and LLVM](https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/). 

Wilfred Hughes. (2014). [Baby Steps to a C Compiler](https://www.wilfred.me.uk/blog/2014/08/27/baby-steps-to-a-c-compiler/).

Continuum Analytics. (2012). [LLVMPY](https://www.llvmpy.org/).

Python. (2023). [Full Grammar specification](https://docs.python.org/3/reference/grammar.html).