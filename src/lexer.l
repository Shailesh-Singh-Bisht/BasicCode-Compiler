%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "parser.tab.h"
#include "error.h"

extern int yylineno;
%}


DIGIT       [0-9]
ID_START    [a-zA-Z_]
ID_CHAR     [a-zA-Z0-9_]
STRING      \"([^\\\"]|\\.)*\"

%%

"let"       { return LET; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"for"       { return FOR; }
"return"    { return RETURN; }
"func"      { return FUNC; }
"print"     { return PRINT; }

"int"       { return INT_TYPE; }
"float"     { return FLOAT_TYPE; }
"bool"      { return BOOL_TYPE; }
"string"    { return STRING_TYPE; }
"void"      { return VOID_TYPE; }

"true"      { yylval.boolean = true; return BOOLEAN_LITERAL; }
"false"     { yylval.boolean = false; return BOOLEAN_LITERAL; }

"=="        { return EQ; }
"!="        { return NEQ; }
"<="        { return LE; }
">="        { return GE; }
"<"         { return LT; }
">"         { return GT; }
"&&"        { return AND; }
"||"        { return OR; }
"!"         { return NOT; }

"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }
"%"         { return MOD; }
"="         { return ASSIGN; }

"("         { return LPAREN; }
")"         { return RPAREN; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
","         { return COMMA; }
";"         { return SEMICOLON; }

{STRING} {
    yylval.str = strdup(yytext);
    return STRING_LITERAL;
}

{DIGIT}+"."{DIGIT}+  { 
    yylval.floatVal = atof(yytext); 
    return FLOAT_LITERAL; 
}

{DIGIT}+    { 
    yylval.intVal = atoi(yytext); 
    return INT_LITERAL; 
}

{ID_START}{ID_CHAR}* {
    if (strcmp(yytext, "let") == 0) return LET;
    if (strcmp(yytext, "func") == 0) return FUNC;
    if (strcmp(yytext, "if") == 0) return IF;
    if (strcmp(yytext, "else") == 0) return ELSE;
    if (strcmp(yytext, "while") == 0) return WHILE;
    if (strcmp(yytext, "for") == 0) return FOR;
    if (strcmp(yytext, "return") == 0) return RETURN;
    if (strcmp(yytext, "print") == 0) return PRINT;
    
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

\/\/[^\n]*  { /* skip single-line comments */ }
"/*"([^*]|\*+[^*/])*\*+"/"  { /* multi-line comment */ }

[\n]        { ++yylineno; }
[ \t\r]+    { /* skip whitespace */ }

.           { 
    reportError(ErrorType::SyntaxError, std::string("Unknown character: ") + yytext, yylineno);
    return INVALID;
}

%%

int yywrap() {
    return 1;
}
