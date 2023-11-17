%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(const char *s);
    extern int yylex(void);
    extern char *yytext; 
%}

%token T_GREETINGS T_INTRODUCE T_AS T_INTEGER_TYPE T_STRING_TYPE
%token T_DECLARE_VALUE T_ASSIGN T_ASSIGN_VALUE T_CONDITIONAL T_HOLDS_TRUE
%token T_OTHERWISE T_WHILST T_FIRSTLY T_CONCLUSION T_OR
%token T_AND T_EQUIVALENCE T_GREATER T_LESSER T_ADDITION
%token T_SUBTRACTION T_CONCATENATION T_MULTIPLICATION T_DIVISON T_POSITIVELY
%token T_NEGATIVELY T_NOT T_IDENTIFIER T_STRING T_NUMBER T_NEW_SENTENCE

%%

ElegantConversation: Greeting SentenceList ;

Greeting: T_GREETINGS T_NEW_SENTENCE ;

SentenceList: /* empty */
            | SentenceList Sentence ;

Sentence:  Declare
        | Assign
        | Conditional
        | Loop ;

Declare: T_INTRODUCE T_IDENTIFIER T_AS Type OptionalValue T_NEW_SENTENCE ;

Type: T_INTEGER_TYPE 
    | T_STRING_TYPE ;

OptionalValue: /* empty */
            | T_DECLARE_VALUE BooleanExpression ;

Assign: T_ASSIGN T_IDENTIFIER T_ASSIGN_VALUE BooleanExpression T_NEW_SENTENCE ;

Conditional: T_CONDITIONAL BooleanExpression T_HOLDS_TRUE Block OptionalElse ;

OptionalElse: /* empty */
            | T_OTHERWISE Block ;

Loop: T_WHILST BooleanExpression T_HOLDS_TRUE Block ;

Block: T_FIRSTLY SentenceList T_CONCLUSION T_NEW_SENTENCE ;

BooleanExpression: BooleanClause
                | BooleanExpression T_OR BooleanClause  ;

BooleanClause: RelationalExpression
            | BooleanClause T_AND RelationalExpression ;

RelationalExpression: Expression
                    | RelationalExpression RelationalOp Expression;

RelationalOp: T_EQUIVALENCE 
            | T_GREATER 
            | T_LESSER ;

Expression: Term 
          | Expression ArithmeticAddSubConcatOp Term ;

ArithmeticAddSubConcatOp: T_ADDITION 
                        | T_SUBTRACTION 
                        | T_CONCATENATION ;

Term: Factor 
    | Term ArithmeticMultDivOp Factor ;

ArithmeticMultDivOp: T_MULTIPLICATION 
                   | T_DIVISON ;

Factor: T_NUMBER 
      | T_STRING
      | T_IDENTIFIER 
      | UnaryOp Factor ;

UnaryOp: T_POSITIVELY 
       | T_NEGATIVELY 
       | T_NOT ;

%%

void yyerror(const char *s) {
    extern int yylval;   // Token value
    fprintf(stderr, "Error near token '%s': %s\n", yytext, s);
}

int main(void) {
    extern int yy_flex_debug;
    yy_flex_debug = 1;
    if (yyparse()) {
        printf("Error in parsing!\n");
        return 1;
    }
    return 0;
}
