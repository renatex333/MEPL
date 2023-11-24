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
    PyObject *pName = PyUnicode_FromString("compiler.src.semantic.AbstractSyntaxTreeNodes");
    if (!pModule) {
        pModule = PyImport_Import(pName);
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
    Py_DECREF(pChildren);
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
    Py_DECREF(pChildren);
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
    PyObject *pValue = PyUnicode_FromString("ElegantAssignment");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $2);
    PyList_Append(pChildren, $4);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantAssignment", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
};

Conditional: T_CONDITIONAL BooleanExpression T_HOLDS_TRUE Block OptionalElse    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantConditional");
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
    Py_DECREF(pChildren);
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
    PyObject *pValue = PyUnicode_FromString("ElegantLoop");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $2);
    PyList_Append(pChildren, $4);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantLoop", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
};

Solicit: T_SOLICITATION Identifier T_NEW_SENTENCE   {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantSolicitation");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $2);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantSolicitation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
};

Display: T_DISPLAY BooleanExpression T_NEW_SENTENCE {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantDisplay");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $2);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantDisplay", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
};

Block: T_FIRSTLY BlockSentenceList T_CONCLUSION T_NEW_SENTENCE   {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantBlock");

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, $2);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantBlock", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
};

BlockSentenceList:  /* empty */ {
    $$ = PyList_New(0); // Base case: an empty list
}
            | BlockSentenceList Sentence {
    if (!PyList_Check($1)) {
        yyerror("Expected a list as the first argument");
        $$ = NULL;
    } else {
        PyList_Append($1, $2);
        $$ = $1;    // Assign the modified list back to $$
    }
};

BooleanExpression: BooleanClause    {
    $$ = $1;
}
                | BooleanExpression T_OR BooleanClause  {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("or");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $1);
    PyList_Append(pChildren, $3);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantBinaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
};

BooleanClause: RelationalExpression {
    $$ = $1;
}
            | BooleanClause T_AND RelationalExpression  {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("and");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $1);
    PyList_Append(pChildren, $3);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantBinaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
};

RelationalExpression: Expression    {
    $$ = $1;
}
                    | RelationalExpression RelationalOp Expression  {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = $2;
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $1);
    PyList_Append(pChildren, $3);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantBinaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
};

RelationalOp: T_EQUIVALENCE {
    $$ = PyUnicode_FromString(yytext); 
}
            | T_DIFFERENCE  {
    $$ = PyUnicode_FromString(yytext); 
}
            | T_GREATER     {
    $$ = PyUnicode_FromString(yytext); 
}
            | T_LESSER      {
    $$ = PyUnicode_FromString(yytext); 
};

Expression: Term    {
    $$ = $1;
} 
          | Expression ArithmeticAddSubConcatOp Term    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = $2;
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $1);
    PyList_Append(pChildren, $3);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantBinaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
};

ArithmeticAddSubConcatOp: T_ADDITION    {
    $$ = PyUnicode_FromString(yytext); 
}
                        | T_SUBTRACTION {
    $$ = PyUnicode_FromString(yytext); 
}
                        | T_CONCATENATION   {
    $$ = PyUnicode_FromString(yytext); 
};

Term: Factor    {
    $$ = $1;
} 
    | Term ArithmeticMultDivOp Factor   {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = $2;
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $1);
    PyList_Append(pChildren, $3);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantBinaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
};

ArithmeticMultDivOp: T_MULTIPLICATION   {
    $$ = PyUnicode_FromString(yytext); 
}
                   | T_DIVISON  {
    $$ = PyUnicode_FromString(yytext); 
};

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
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
      | T_STRING    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString(yytext);
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantStringValue", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
      | UnaryOp Factor  {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = $1;
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, $2);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    $$ = create_ast_node("ElegantUnaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
      | Identifier ;

UnaryOp: T_POSITIVELY   {
    $$ = PyUnicode_FromString(yytext); 
}
       | T_NEGATIVELY   {
    $$ = PyUnicode_FromString(yytext); 
}
       | T_NOT  {
    $$ = PyUnicode_FromString(yytext); 
};

%%

void yyerror(const char *s) {
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
    
    if (yyparse() == 0 && pRootNode != NULL) {
        PyObject_CallMethod(pRootNode, "evaluate", "OO", pSymbolTable, pCodeGenerator);
    } else {
        printf("Error in parsing!\n");
        return 1;
    }

    PyObject_CallMethod(pCodeGenerator, "create_file", NULL);

    Py_XDECREF(pRootNode);
    Py_XDECREF(pSymbolTable);
    Py_XDECREF(pCodeGenerator);
    Py_Finalize();
    fclose(file);
    return 0;
}

