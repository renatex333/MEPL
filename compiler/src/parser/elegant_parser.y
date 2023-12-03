%{
#define YYSTYPE PyObject *

#include <stdio.h>
#include <stdlib.h>
#include <Python.h>

void yyerror(const char *s);
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;

PyObject *p_root_node = NULL;

PyObject *create_elegant_node(const char *node_type, PyObject *args) {
    static PyObject *p_module = NULL;
    PyObject *p_name = PyUnicode_FromString("compiler.src.semantic.ElegantAbstractSyntaxTreeNodes");
    if (!p_module) {
        p_module = PyImport_Import(p_name);
        if (!p_module) {
            PyErr_Print();
            fprintf(stderr, "Regrettably, the loading of the 'ElegantAbstractSyntaxTreeNodes' module_name was not met with success.\n");
            return NULL;
        }
    }

    PyObject *p_class = PyObject_GetAttrString(p_module, node_type);
    if (!p_class || !PyCallable_Check(p_class)) {
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Unable to find the class_name '%s', much to our regret.\n", node_type);
        Py_XDECREF(p_class);
        return NULL;
    }

    PyObject *p_instance = PyObject_CallObject(p_class, args);
    Py_DECREF(p_class);
    if (!p_instance) {
        PyErr_Print();
        fprintf(stderr, "Unfortunately, creating an instance of '%s' was unsuccessful.\n", node_type);

        return NULL;
    }

    return p_instance;
}

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
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString("ElegantConversation");

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, $2);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        p_root_node = create_elegant_node("ElegantConversation", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_args_tuple);
    };

Greeting:
    T_GREETINGS T_NEW_SENTENCE ;

SentenceList:
    SentenceList Sentence {
        if (!PyList_Check($1)) {
            yyerror("Anticipation was for a list to graciously present itself as the first argument.");
            $$ = NULL;
        } else {
            PyList_Append($1, $2);
        }
    }
    | Sentence {
        PyObject *single_sentence_list = PyList_New(1);
        PyList_SetItem(single_sentence_list, 0, $1);
        $$ = single_sentence_list;
    }
    | YYEOF {
        $$ = PyList_New(0);
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
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = $4;
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $2);
        if ($5 != 0) {
            PyList_Append(p_children, $5);
        }

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantVariableDeclaration", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

Identifier:
    T_IDENTIFIER {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString(yytext);
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantIdentifier", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

Type:
    T_INTEGER_TYPE {
        $$ = PyUnicode_FromString("INT");
    }
    | T_STRING_TYPE {
        $$ = PyUnicode_FromString("STRING");
    };

OptionalValue:
    /* empty */ {
        $$ = 0;
    }
    | T_DECLARE_VALUE BooleanExpression {
        $$ = $2;
    };

Assign:
    T_ASSIGN Identifier T_ASSIGN_VALUE BooleanExpression T_NEW_SENTENCE {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString("ElegantAssignment");
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $2);
        PyList_Append(p_children, $4);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantAssignment", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

Conditional:
    T_CONDITIONAL BooleanExpression T_HOLDS_TRUE Block OptionalElse {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString("ElegantConditional");
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $2);
        PyList_Append(p_children, $4);
        if ($5 != 0) {
            PyList_Append(p_children, $5);
        }

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantConditional", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

OptionalElse:
    /* empty */ {
        $$ = 0;
    }
    | T_OTHERWISE Block {
        $$ = $2;
    };

Loop:
    T_WHILST BooleanExpression T_HOLDS_TRUE Block {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString("ElegantLoop");
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $2);
        PyList_Append(p_children, $4);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantLoop", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

Solicit:
    T_SOLICITATION Identifier T_NEW_SENTENCE {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString("ElegantSolicitation");
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $2);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantSolicitation", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

Display:
    T_DISPLAY BooleanExpression T_NEW_SENTENCE {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString("ElegantDisplay");
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $2);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantDisplay", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

Block:
    T_FIRSTLY BlockSentenceList T_CONCLUSION T_NEW_SENTENCE {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString("ElegantBlock");

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, $2);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantBlock", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_args_tuple);
    };

BlockSentenceList:
    /* empty */ {
        $$ = PyList_New(0);
    }
    | BlockSentenceList Sentence {
        if (!PyList_Check($1)) {
            yyerror("Anticipation was for a list to graciously present itself as the first argument.");
            $$ = NULL;
        } else {
            PyList_Append($1, $2);
            $$ = $1;
        }
    };

BooleanExpression:
    BooleanClause {
        $$ = $1;
    }
    | BooleanExpression T_OR BooleanClause {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString("or");
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $1);
        PyList_Append(p_children, $3);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantBinaryOperation", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

BooleanClause:
    RelationalExpression {
        $$ = $1;
    }
    | BooleanClause T_AND RelationalExpression {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString("and");
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $1);
        PyList_Append(p_children, $3);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantBinaryOperation", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

RelationalExpression:
    Expression {
        $$ = $1;
    }
    | RelationalExpression RelationalOp Expression {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = $2;
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $1);
        PyList_Append(p_children, $3);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantBinaryOperation", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

RelationalOp:
    T_EQUIVALENCE {
        $$ = PyUnicode_FromString(yytext); 
    }
    | T_DIFFERENCE {
        $$ = PyUnicode_FromString(yytext); 
    }
    | T_GREATER {
        $$ = PyUnicode_FromString(yytext); 
    }
    | T_LESSER {
        $$ = PyUnicode_FromString(yytext); 
    };

Expression:
    Term {
        $$ = $1;
    }
    | Expression ArithmeticAddSubConcatOp Term {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = $2;
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $1);
        PyList_Append(p_children, $3);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantBinaryOperation", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

ArithmeticAddSubConcatOp:
    T_ADDITION {
        $$ = PyUnicode_FromString(yytext); 
    }
    | T_SUBTRACTION {
        $$ = PyUnicode_FromString(yytext); 
    }
    | T_CONCATENATION {
        $$ = PyUnicode_FromString(yytext); 
    };

Term:
    Factor {
        $$ = $1;
    } 
    | Term ArithmeticMultDivOp Factor {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = $2;
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $1);
        PyList_Append(p_children, $3);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantBinaryOperation", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    };

ArithmeticMultDivOp:
    T_MULTIPLICATION {
        $$ = PyUnicode_FromString(yytext); 
    }
    | T_DIVISON {
        $$ = PyUnicode_FromString(yytext); 
    };

Factor:
    T_NUMBER {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString(yytext);
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantIntegerValue", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    }
    | T_STRING {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = PyUnicode_FromString(yytext);
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantStringValue", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    }
    | UnaryOp Factor {
        PyObject *p_args_list = PyList_New(0);
        PyObject *p_value = $1;
        PyObject *p_children = PyList_New(0);

        PyList_Append(p_children, $2);

        PyList_Append(p_args_list, p_value);
        PyList_Append(p_args_list, p_children);

        PyObject *p_args_tuple = PyList_AsTuple(p_args_list);
        $$ = create_elegant_node("ElegantUnaryOperation", p_args_tuple);
        
        Py_DECREF(p_args_list);
        Py_DECREF(p_value);
        Py_DECREF(p_children);
        Py_DECREF(p_args_tuple);
    }
    | Identifier ;

UnaryOp:
    T_POSITIVELY {
        $$ = PyUnicode_FromString(yytext); 
    }
    | T_NEGATIVELY {
        $$ = PyUnicode_FromString(yytext); 
    }
    | T_NOT {
        $$ = PyUnicode_FromString(yytext); 
    };

%%

void yyerror(const char *s) {
    fprintf(stderr, "An error was encountered near the token '%s': %s\n", yytext, s);
}

PyObject *createInstance(const char* module_name, const char* class_name, PyObject *args) {
    PyObject *p_name = PyUnicode_FromString(module_name);
    PyObject *p_module = PyImport_Import(p_name);
    Py_DECREF(p_name);
    if (p_module == NULL) return NULL;

    PyObject *p_class = PyObject_GetAttrString(p_module, class_name);
    Py_DECREF(p_module);
    if (p_class == NULL) return NULL;

    PyObject *p_instance;
    if (args != NULL) {
        p_instance = PyObject_CallObject(p_class, args);
    } else {
        p_instance = PyObject_CallObject(p_class, NULL);
    }
    Py_DECREF(p_class);
    if (p_instance == NULL) {
        PyErr_Print();
        fprintf(stderr, "Unfortunately, creating an instance of '%s' was unsuccessful.\n", class_name);
        return NULL;
    }

    return p_instance;
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

    Py_Initialize();

    PyObject *p_symbol_table = createInstance("compiler.src.semantic.ElegantSymbolTable", "SymbolTable", NULL);

    PyObject *p_filename = PyUnicode_FromString(argv[1]);
    PyObject *p_args = PyTuple_New(1);
    PyTuple_SetItem(p_args, 0, p_filename);
    PyObject *p_code_generator = createInstance("compiler.src.codegen.ElegantCodeGenerator", "CodeGen", p_args);
    Py_DECREF(p_args);
    
    if (yyparse() == 0 && p_root_node != NULL) {
        PyObject_CallMethod(p_root_node, "evaluate", "OO", p_symbol_table, p_code_generator);
    } else {
        printf("Error in parsing!\n");
        return 1;
    }

    PyObject_CallMethod(p_code_generator, "create_file", NULL);

    Py_XDECREF(p_root_node);
    Py_XDECREF(p_symbol_table);
    Py_XDECREF(p_code_generator);
    Py_Finalize();
    fclose(file);
    return 0;
}
