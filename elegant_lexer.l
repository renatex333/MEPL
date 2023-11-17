%{
#include "elegant_parser.tab.h"
%}


%%
"Greetings"                     { return T_GREETINGS; }
"I introduce"                   { return T_INTRODUCE; }
"as"                            { return T_AS; }
"an integer"                    { return T_INTEGER_TYPE; }
"a string"                      { return T_STRING_TYPE; }
"carrying the value of"         { return T_DECLARE_VALUE; }
"Please, let"                   { return T_ASSIGN; }
"be given the value of"         { return T_ASSIGN_VALUE; }
"In the event that"             { return T_CONDITIONAL; }
"holds true:"                   { return T_HOLDS_TRUE; }
"Otherwise:"                    { return T_OTHERWISE; }
"Whilst"                        { return T_WHILST; }
"Firstly,"                      { return T_FIRSTLY; }
"... as a conclusion to the matter" { return T_CONCLUSION; }
"or"                            { return T_OR; }
"and"                           { return T_AND; }
"equates to"                    { return T_EQUIVALENCE; }
"exceeds"                       { return T_GREATER; }
"is less than"                  { return T_LESSER; }
"added to"                      { return T_ADDITION; }
"subtracted by"                 { return T_SUBTRACTION; }
"concatenated with"             { return T_CONCATENATION; }
"multiplied by"                 { return T_MULTIPLICATION; }
"divided by"                    { return T_DIVISON; }
"positively"                    { return T_POSITIVELY; }
"negatively"                    { return T_NEGATIVELY; }
"not"                           { return T_NOT; }
[a-zA-Z_][a-zA-Z_0-9]*          { return T_IDENTIFIER; }
\"([^\\\"]|\\(.|\n)|[@#$%^&*()_+{}[\]|:;'<>,.?/!~-])*\" { return T_STRING; }
[0-9]+[ ]                       { return T_NUMBER; }
"."                             { return T_NEW_SENTENCE; }
\n                              { /* handle new lines */ }
[ \t\r]+                        { /* ignore extra whitespace */ }
.                               { /* handle other characters */ }
%%
