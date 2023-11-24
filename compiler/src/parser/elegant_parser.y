%{
#define YYSTYPE PyObject *

#include <stdio.h>
#include <stdlib.h>
#include <Python.h>

void yyerror(const char *s);
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;

PyObject *pRootNode = NULL;

PyObject *create_ast_node(const char *node_type, PyObject *args) {
    static PyObject *pModule = NULL;
    if (!pModule) {
        pModule = PyImport_Import(PyUnicode_DecodeFSDefault("AbstractSyntaxTreeNodes"));
        if (!pModule) {
            PyErr_Print();
            fprintf(stderr, "Failed to load 'AbstractSyntaxTreeNodes' module\n");
            return NULL;
        }
    }

    PyObject *pClass = PyObject_GetAttrString(pModule, node_type);
    if (!pClass || !PyCallable_Check(pClass)) {
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Failed to find class '%s'\n", node_type);
        Py_XDECREF(pClass);
        return NULL;
    }

    PyObject *pInstance = PyObject_CallObject(pClass, args);
    Py_DECREF(pClass);
    if (!pInstance) {
        PyErr_Print();
        fprintf(stderr, "Failed to create instance of '%s'\n", node_type);
        return NULL;
    }

    return pInstance;
}

%}

%token T_GREETINGS T_INTRODUCE T_AS T_INTEGER_TYPE T_STRING_TYPE
%token T_DECLARE_VALUE T_ASSIGN T_ASSIGN_VALUE T_CONDITIONAL T_HOLDS_TRUE
%token T_OTHERWISE T_WHILST T_SOLICITATION T_DISPLAY T_FIRSTLY T_CONCLUSION T_OR
%token T_AND T_EQUIVALENCE T_DIFFERENCE T_GREATER T_LESSER T_ADDITION
%token T_SUBTRACTION T_CONCATENATION T_MULTIPLICATION T_DIVISON T_POSITIVELY
%token T_NEGATIVELY T_NOT T_IDENTIFIER T_STRING T_NUMBER T_NEW_SENTENCE

%%

ElegantConversation: Greeting SentenceList {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantConversation");

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, $2);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    pRootNode = create_ast_node("ElegantConversation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
};

Greeting: T_GREETINGS T_NEW_SENTENCE ;

SentenceList: SentenceList Sentence {
    if (!PyList_Check($1)) {
        yyerror("Expected a list as the first argument");
        $$ = NULL;
    } else {
        PyList_Append($1, $2);
    }
}
            | Sentence  {
    PyObject *singleSentenceList = PyList_New(1);
    PyList_SetItem(singleSentenceList, 0, $1); // $1 refers to the single Sentence node
    $$ = singleSentenceList;
}
            | YYEOF {
    $$ = PyList_New(0); // Base case: an empty list
};

Sentence: Declare
        | Assign
        | Conditional
        | Loop
        | Solicit
        | Display ;

Declare: T_INTRODUCE Identifier T_AS Type OptionalValue T_NEW_SENTENCE  {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = $4;
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $2);
    if ($5 != 0) {
        PyList_Append(pChildren, $5);
    }

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantVariableDeclaration", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
};

Identifier: T_IDENTIFIER    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString(yytext);
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantIdentifier", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
};

Type: T_INTEGER_TYPE    {
    $$ = PyUnicode_FromString("INT");
}
    | T_STRING_TYPE {
    $$ = PyUnicode_FromString("STRING");
};

OptionalValue: /* empty */  {
    $$ = 0;
}
            | T_DECLARE_VALUE BooleanExpression {
    $$ = $2;
};

Assign: T_ASSIGN Identifier T_ASSIGN_VALUE BooleanExpression T_NEW_SENTENCE {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("=");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $2);
    PyList_Append(pChildren, $4);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantAssignment", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
};

Conditional: T_CONDITIONAL BooleanExpression T_HOLDS_TRUE Block OptionalElse    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("If");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $2);
    PyList_Append(pChildren, $4);
    if ($5 != 0) {
        PyList_Append(pChildren, $5);
    }

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantConditional", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
};

OptionalElse: /* empty */   {
    $$ = 0;
}
            | T_OTHERWISE Block {
    $$ = $2;
};

Loop: T_WHILST BooleanExpression T_HOLDS_TRUE Block {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("While");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $2);
    PyList_Append(pChildren, $4);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantLoop", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
};

Solicit: T_SOLICITATION Identifier T_NEW_SENTENCE   {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("Scan");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $2);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantSolicitation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
};

Display: T_DISPLAY BooleanExpression T_NEW_SENTENCE {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("Print");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $2);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantDisplay", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
};

Block: T_FIRSTLY BlockSentenceList T_NEW_SENTENCE   {

};

BlockSentenceList: BlockSentenceList Sentence {
    if (!PyList_Check($1)) {
        yyerror("Expected a list as the first argument");
        $$ = NULL;
    } else {
        PyList_Append($1, $2);
    }
}
            | Sentence T_CONCLUSION {
    PyObject *singleSentenceList = PyList_New(1);
    PyList_SetItem(singleSentenceList, 0, $1); // $1 refers to the single Sentence node
    $$ = singleSentenceList;
}
            | T_CONCLUSION {
    $$ = PyList_New(0); // Base case: an empty list
};

BooleanExpression: BooleanClause    {
    $$ = $1;
}
                | BooleanExpression T_OR BooleanClause  ;

BooleanClause: RelationalExpression {
    $$ = $1;
}
            | BooleanClause T_AND RelationalExpression ;

RelationalExpression: Expression    {
    $$ = $1;
}
                    | RelationalExpression RelationalOp Expression;

RelationalOp: T_EQUIVALENCE 
            | T_DIFFERENCE
            | T_GREATER 
            | T_LESSER ;

Expression: Term    {
    $$ = $1;
} 
          | Expression ArithmeticAddSubConcatOp Term ;

ArithmeticAddSubConcatOp: T_ADDITION 
                        | T_SUBTRACTION
                        | T_CONCATENATION ;

Term: Factor    {
    $$ = $1;
} 
    | Term ArithmeticMultDivOp Factor ;

ArithmeticMultDivOp: T_MULTIPLICATION 
                   | T_DIVISON ;

Factor: T_NUMBER    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString(yytext);
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantIntegerValue", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
}
      | T_STRING
      | Identifier 
      | UnaryOp Factor ;

UnaryOp: T_POSITIVELY 
       | T_NEGATIVELY 
       | T_NOT ;

%%

void yyerror(const char *s) {
    extern YYSTYPE yylval;
    fprintf(stderr, "Error near token '%s': %s\n", yytext, s);
}

PyObject *create_instance(const char* module_name, const char* class_name, PyObject *args) {
    PyObject *pName = PyUnicode_FromString(module_name);
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (pModule == NULL) return NULL;

    PyObject *pClass = PyObject_GetAttrString(pModule, class_name);
    Py_DECREF(pModule);
    if (pClass == NULL) return NULL;

    PyObject *pInstance;
    if (args != NULL) {
        pInstance = PyObject_CallObject(pClass, args);
    } else {
        pInstance = PyObject_CallObject(pClass, NULL);
    }
    Py_DECREF(pClass);
    if (pInstance == NULL) {
        PyErr_Print();
        fprintf(stderr, "Failed to create instance of '%s'\n", class_name);
        return NULL;
    }

    return pInstance;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror(argv[1]);
        return 1;
    }

    yyin = file;

    Py_Initialize();

    PyObject *pSymbolTable = create_instance("compiler.src.semantic.SymbolTable", "SymbolTable", NULL);

    PyObject *pFilename = PyUnicode_FromString(argv[1]);
    PyObject *pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, pFilename);
    PyObject *pCodeGenerator = create_instance("compiler.src.codegen.CodeGenerator", "CodeGen", pArgs);
    Py_DECREF(pArgs);

    PyObject_CallMethod(pCodeGenerator, "start", NULL);
    
    if (yyparse() == 0 && pRootNode != NULL) {
        PyObject_CallMethod(pRootNode, "evaluate", "OO", pSymbolTable, pCodeGenerator);
    } else {
        printf("Error in parsing!\n");
    }

    PyObject_CallMethod(pCodeGenerator, "finish", NULL);

    Py_XDECREF(pRootNode);
    Py_XDECREF(pSymbolTable);
    Py_XDECREF(pCodeGenerator);
    Py_Finalize();
    fclose(file);
    return 0;
}

