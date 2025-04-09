#ifndef LEXER_H
#define LEXER_H

#ifdef __cplusplus
extern "C" {
#endif

// Lexical analyzer function provided by Flex
int yylex();

// Error handling function used by Bison
void yyerror(const char* msg);

// Flex sets this to keep track of line numbers
extern int yylineno;

#ifdef __cplusplus
}
#endif

#endif // LEXER_H
