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

```
# ========================= START OF THE GRAMMAR =========================

# General grammatical elements and rules:
#
# * Strings with double quotes (") denote SOFT KEYWORDS
# * Strings with single quotes (') denote KEYWORDS
# * Upper case names (NAME) denote tokens in the Grammar/Tokens file
# * Rule names starting with "invalid_" are used for specialized syntax errors
#     - These rules are NOT used in the first pass of the parser.
#     - Only if the first pass fails to parse, a second pass including the invalid
#       rules will be executed.
#     - If the parser fails in the second phase with a generic syntax error, the
#       location of the generic failure of the first pass will be used (this avoids
#       reporting incorrect locations due to the invalid rules).
#     - The order of the alternatives involving invalid rules matter
#       (like any rule in PEG).
#
# Grammar Syntax (see PEP 617 for more information):
#
# rule_name: expression
#   Optionally, a type can be included right after the rule name, which
#   specifies the return type of the C or Python function corresponding to the
#   rule:
# rule_name[return_type]: expression
#   If the return type is omitted, then a void * is returned in C and an Any in
#   Python.
# e1 e2
#   Match e1, then match e2.
# e1 | e2
#   Match e1 or e2.
#   The first alternative can also appear on the line after the rule name for
#   formatting purposes. In that case, a | must be used before the first
#   alternative, like so:
#       rule_name[return_type]:
#            | first_alt
#            | second_alt
# ( e )
#   Match e (allows also to use other operators in the group like '(e)*')
# [ e ] or e?
#   Optionally match e.
# e*
#   Match zero or more occurrences of e.
# e+
#   Match one or more occurrences of e.
# s.e+
#   Match one or more occurrences of e, separated by s. The generated parse tree
#   does not include the separator. This is otherwise identical to (e (s e)*).
# &e
#   Succeed if e can be parsed, without consuming any input.
# !e
#   Fail if e can be parsed, without consuming any input.
# ~
#   Commit to the current alternative, even if it fails to parse.
#

ELEGANT CONVERSATION = { STATEMENT }
BLOCK = "Begin", "\n", { STATEMENT }, "End" ;
STATEMENT = ( λ | ASSIGN | DISPLAY | CONDITIONAL | LOOP | DECLARE), "\n" ;
ASSIGN = "Please let", IDENTIFIER, "be", BOOLEAN EXPRESSION ;
DISPLAY = "Kindly show", "(", BOOLEAN EXPRESSION, ")" ;
CONDITIONAL = "Should", BOOLEAN EXPRESSION, "be so,", BLOCK, { "Otherwise,", BLOCK } ;
LOOP = "Whilst", ASSIGN, "and", BOOLEAN EXPRESSION, "and then", ASSIGN, BLOCK ;
DECLARE = "I introduce", IDENTIFIER, "as", ("an integer" | "a string"), [ "being", BOOLEAN EXPRESSION ] ;
BOOLEAN EXPRESSION = BOOLEAN CLAUSE, { "or", BOOLEAN CLAUSE } ;
BOOLEAN CLAUSE = RELATIONAL EXPRESSION, { "and", RELATIONAL EXPRESSION } ;
RELATIONAL EXPRESSION = EXPRESSION, { ("equates to" | "exceeds" | "is less than"), EXPRESSION } ;
EXPRESSION = COMPONENT, { ("added to" | "subtracted by" | "concatenated with"), COMPONENT } ;
COMPONENT = ELEMENT, { ("multiplied by" | "divided by"), ELEMENT } ;
ELEMENT = NUMBER | STRING | IDENTIFIER | (("positively" | "negatively" | "not"), ELEMENT) | "(", BOOLEAN EXPRESSION, ")" | INPUT ;
INPUT = "Humbly request", "(", ")" ;
IDENTIFIER = LETTER, { LETTER | DIGIT | "_" } ;
NUMBER = DIGIT, { DIGIT } ;
STRING = ( "“" | "‘" ), { λ | LETTER | DIGIT }, ( "”" | "’" ) ;
LETTER = ( a | ... | z | A | ... | Z ) ;
DIGIT = ( 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 ) ;
```

## References

Aaron Myles Landwehr. (2012). [Flex/Bison Tutorial](https://www.capsl.udel.edu/courses/cpeg421/2012/slides/Tutorial-Flex_Bison.pdf).

Joe "begriffs" Nelson. (2021). [Practical parsing with Flex and Bison](https://begriffs.com/posts/2021-11-28-practical-parsing.html). 

Loren Segal. (2009). [Writing Your Own Toy Compiler Using Flex, Bison and LLVM](https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/). 

Wilfred Hughes. (2014). [Baby Steps to a C Compiler](https://www.wilfred.me.uk/blog/2014/08/27/baby-steps-to-a-c-compiler/).

Continuum Analytics. (2012). [LLVMPY](https://www.llvmpy.org/).

Python. (2023). [Full Grammar specification](https://docs.python.org/3/reference/grammar.html).