%{
#define YYSTYPE ASTNode*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/elegant_ast.h"

void yyerror(const char *s);
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;

ASTNode *root_node = NULL;

%}

%token  T_GREETINGS        T_INTRODUCE       T_AS            T_INTEGER_TYPE    T_STRING_TYPE
%token  T_DECLARE_VALUE    T_ASSIGN          T_ASSIGN_VALUE  T_CONDITIONAL     T_HOLDS_TRUE
%token  T_OTHERWISE        T_WHILST          T_SOLICITATION  T_DISPLAY         T_FIRSTLY
%token  T_CONCLUSION       T_OR              T_AND           T_EQUIVALENCE     T_DIFFERENCE
%token  T_GREATER          T_LESSER          T_ADDITION      T_SUBTRACTION     T_CONCATENATION
%token  T_MULTIPLICATION   T_DIVISON         T_POSITIVELY    T_NEGATIVELY      T_NOT
%token  T_IDENTIFIER       T_STRING          T_NUMBER        T_NEW_SENTENCE


%%

ElegantConversation:
    Greeting SentenceList {
        root_node = create_ast_node(NODE_CONVERSATION, "ElegantConversation");
        add_child(root_node, $2);
        $$ = root_node;
    };

Greeting:
    T_GREETINGS T_NEW_SENTENCE {
        $$ = create_ast_node(NODE_NOP, NULL);
    };

SentenceList:
    SentenceList Sentence {
        add_child($1, $2);
        $$ = $1;
    }
    | Sentence {
        ASTNode *list = create_ast_node(NODE_BLOCK, "SentenceList");
        add_child(list, $1);
        $$ = list;
    }
    | YYEOF {
        $$ = create_ast_node(NODE_BLOCK, "EmptyList");
    };

Sentence:
        Declare
        | Assign
        | Conditional
        | Loop
        | Solicit
        | Display ;

Declare:
    T_INTRODUCE Identifier T_AS Type OptionalValue T_NEW_SENTENCE {
        $$ = create_ast_node(NODE_DECLARATION, $4->value);
        add_child($$, $2);
        if ($5) {
            add_child($$, $5);
        }
        free_ast_node($4);
    };

Identifier:
    T_IDENTIFIER {
        $$ = create_ast_node(NODE_IDENTIFIER, yytext);
    };

Type:
    T_INTEGER_TYPE {
        $$ = create_ast_node(NODE_NOP, "INT");
    }
    | T_STRING_TYPE {
        $$ = create_ast_node(NODE_NOP, "STRING");
    };

OptionalValue:
    /* empty */ {
        $$ = NULL;
    }
    | T_DECLARE_VALUE BooleanExpression {
        $$ = $2;
    };

Assign:
    T_ASSIGN Identifier T_ASSIGN_VALUE BooleanExpression T_NEW_SENTENCE {
        $$ = create_ast_node(NODE_ASSIGNMENT, "ElegantAssignment");
        add_child($$, $2);
        add_child($$, $4);
    };

Conditional:
    T_CONDITIONAL BooleanExpression T_HOLDS_TRUE Block OptionalElse {
        $$ = create_ast_node(NODE_CONDITIONAL, "ElegantConditional");
        add_child($$, $2);
        add_child($$, $4);
        if ($5) {
            add_child($$, $5);
        }
    };

OptionalElse:
    /* empty */ {
        $$ = NULL;
    }
    | T_OTHERWISE Block {
        $$ = $2;
    };

Loop:
    T_WHILST BooleanExpression T_HOLDS_TRUE Block {
        $$ = create_ast_node(NODE_LOOP, "ElegantLoop");
        add_child($$, $2);
        add_child($$, $4);
    };

Solicit:
    T_SOLICITATION Identifier T_NEW_SENTENCE {
        $$ = create_ast_node(NODE_SOLICITATION, "ElegantSolicitation");
        add_child($$, $2);
    };

Display:
    T_DISPLAY BooleanExpression T_NEW_SENTENCE {
        $$ = create_ast_node(NODE_DISPLAY, "ElegantDisplay");
        add_child($$, $2);
    };

Block:
    T_FIRSTLY SentenceList T_CONCLUSION T_NEW_SENTENCE {
        $$ = $2;
    };

BooleanExpression:
    BooleanExpression T_OR BooleanClause {
        $$ = create_ast_node(NODE_BINARY_OP, "or");
        add_child($$, $1);
        add_child($$, $3);
    }
    | BooleanClause {
        $$ = $1;
    };

BooleanClause:
    BooleanClause T_AND RelationalExpression {
        $$ = create_ast_node(NODE_BINARY_OP, "and");
        add_child($$, $1);
        add_child($$, $3);
    }
    | RelationalExpression {
        $$ = $1;
    };

RelationalExpression:
    Expression T_EQUIVALENCE Expression {
        $$ = create_ast_node(NODE_BINARY_OP, "equates to");
        add_child($$, $1);
        add_child($$, $3);
    }
    | Expression T_DIFFERENCE Expression {
        $$ = create_ast_node(NODE_BINARY_OP, "differs from");
        add_child($$, $1);
        add_child($$, $3);
    }
    | Expression T_GREATER Expression {
        $$ = create_ast_node(NODE_BINARY_OP, "exceeds");
        add_child($$, $1);
        add_child($$, $3);
    }
    | Expression T_LESSER Expression {
        $$ = create_ast_node(NODE_BINARY_OP, "is less than");
        add_child($$, $1);
        add_child($$, $3);
    }
    | Expression {
        $$ = $1;
    };

Expression:
    Term T_ADDITION Expression {
        $$ = create_ast_node(NODE_BINARY_OP, "added to");
        add_child($$, $3);
        add_child($$, $1);
    }
    | Term T_SUBTRACTION Expression {
        $$ = create_ast_node(NODE_BINARY_OP, "subtracted from");
        add_child($$, $3);
        add_child($$, $1);
    }
    | Term T_CONCATENATION Expression {
        $$ = create_ast_node(NODE_BINARY_OP, "concatenated with");
        add_child($$, $1);
        add_child($$, $3);
    }
    | Term {
        $$ = $1;
    };

Term:
    Factor T_MULTIPLICATION Term {
        $$ = create_ast_node(NODE_BINARY_OP, "multiplied by");
        add_child($$, $1);
        add_child($$, $3);
    }
    | Factor T_DIVISON Term {
        $$ = create_ast_node(NODE_BINARY_OP, "divided by");
        add_child($$, $3);
        add_child($$, $1);
    }
    | Factor {
        $$ = $1;
    };

Factor:
    T_NUMBER {
        $$ = create_ast_node(NODE_INT_VALUE, yytext);
    }
    | T_STRING {
        /* Remove quotes from string */
        char *str = strdup(yytext + 1);
        str[strlen(str) - 1] = '\0';
        $$ = create_ast_node(NODE_STRING_VALUE, str);
        free(str);
    }
    | Identifier {
        $$ = $1;
    }
    | T_POSITIVELY Factor {
        $$ = create_ast_node(NODE_UNARY_OP, "positively");
        add_child($$, $2);
    }
    | T_NEGATIVELY Factor {
        $$ = create_ast_node(NODE_UNARY_OP, "negatively");
        add_child($$, $2);
    }
    | T_NOT Factor {
        $$ = create_ast_node(NODE_UNARY_OP, "not");
        add_child($$, $2);
    };

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parsing error: %s\n", s);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "For usage, kindly proceed as: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror(argv[1]);
        return 1;
    }

    yyin = file;

    /* Initialize LLVM */
    LLVMLinkInMCJIT();
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();

    if (yyparse() != 0 || root_node == NULL) {
        fprintf(stderr, "Error in parsing!\n");
        fclose(file);
        return 1;
    }

    /* Create code generator */
    CodeGenerator *codegen = create_code_generator(argv[1]);

    /* Generate code */
    codegen_evaluate(root_node, codegen, NULL, NULL);

    /* Finalize and output */
    char output_file[512];
    strncpy(output_file, argv[1], sizeof(output_file) - 1);
    char *ext = strrchr(output_file, '.');
    if (ext) *ext = '\0';
    
    codegen_finalize(codegen, output_file);

    /* Cleanup */
    free_ast_node(root_node);
    free_code_generator(codegen);
    fclose(file);

    return 0;
}
