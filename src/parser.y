%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>
#include <string>

#include "../include/ast.h"
#include "../include/symboltable.h"
#include "../include/error.h"

using ASTNodePtr = std::shared_ptr<ASTNode>;
using ASTNodeList = std::vector<ASTNodePtr>;

extern int yylineno;
extern int yylex();
int yyerror(const char *msg);

ASTNodePtr root = nullptr;
SymbolTable symbolTable;  // Global symbol table instance
%}

%union {
    int intVal;
    float floatVal;
    bool boolean;
    char* str;
    void* ptr;
}

%token <str> IDENTIFIER STRING_LITERAL
%token <intVal> INT_LITERAL
%token <floatVal> FLOAT_LITERAL
%token <boolean> BOOLEAN_LITERAL
%token PRINT


%token LET IF ELSE WHILE FOR RETURN FUNC
%token INT_TYPE FLOAT_TYPE BOOL_TYPE STRING_TYPE VOID_TYPE
%token EQ NEQ LE GE LT GT
%token AND OR NOT
%token PLUS MINUS MUL DIV MOD
%token ASSIGN
%token LPAREN RPAREN LBRACE RBRACE COMMA SEMICOLON
%token INVALID

%left OR
%left AND
%left EQ NEQ
%left LT LE GT GE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT

%type <ptr> program statement expression block declaration assignment function call return_stmt if_stmt while_stmt for_stmt
%type <ptr> statements args opt_args call_args opt_call_args

%start program
%%

program:
    statements {
        root = std::make_shared<ASTNode>(NodeType::Program);
        auto list = static_cast<ASTNodeList*>($1);
        root->children = *list;
        delete list;
    }
;

statements:
    statement {
        auto list = new ASTNodeList();
        list->push_back(*static_cast<ASTNodePtr*>($1));
        delete static_cast<ASTNodePtr*>($1);
        $$ = list;
    }
    | statements statement {
        auto list = static_cast<ASTNodeList*>($1);
        list->push_back(*static_cast<ASTNodePtr*>($2));
        delete static_cast<ASTNodePtr*>($2);
        $$ = list;
    }
    

;

statement:
      declaration SEMICOLON       { $$ = $1; }
    | assignment SEMICOLON        { $$ = $1; }
    | function                    { $$ = $1; }
    | return_stmt SEMICOLON       { $$ = $1; }
    | if_stmt                     { $$ = $1; }
    | while_stmt                  { $$ = $1; }
    | for_stmt                    { $$ = $1; }
    | expression SEMICOLON        { $$ = $1; }
    | block                       { $$ = $1; }
    | PRINT LPAREN expression RPAREN SEMICOLON {
    auto node = std::make_shared<ASTNode>(NodeType::FunctionCall, std::string("print")); 
    node->children.push_back(*static_cast<ASTNodePtr*>($3));
    $$ = new ASTNodePtr(node);
    delete static_cast<ASTNodePtr*>($3);
}
;


block:
    LBRACE {
        symbolTable.enterScope();
    } statements RBRACE {
        auto node = std::make_shared<ASTNode>(NodeType::Block);
        node->children = *static_cast<ASTNodeList*>($3);
        delete static_cast<ASTNodeList*>($3);
        symbolTable.exitScope();
        $$ = new ASTNodePtr(node);
    }
;

declaration:
    LET IDENTIFIER ASSIGN expression {
        auto node = std::make_shared<ASTNode>(NodeType::Declaration, std::string($2));
        auto expr = *static_cast<ASTNodePtr*>($4);
        node->children.push_back(expr);
        node->valueType = expr->valueType;  // Inherit type from the expression
        
        // Add to symbol table with proper type
        symbolTable.declare(std::string($2), expr->valueType, SymbolType::Variable);
        
        delete static_cast<ASTNodePtr*>($4);
        $$ = new ASTNodePtr(node);
    }
;


assignment:
    IDENTIFIER ASSIGN expression {
        auto node = std::make_shared<ASTNode>(NodeType::Assignment, std::string($1));
        node->children.push_back(*static_cast<ASTNodePtr*>($3));
        delete static_cast<ASTNodePtr*>($3);
        $$ = new ASTNodePtr(node);
    }
;


function:
    FUNC IDENTIFIER LPAREN opt_args RPAREN block {
        auto node = std::make_shared<ASTNode>(NodeType::Function, std::string($2));
        auto args = static_cast<ASTNodeList*>($4);
        for (auto& arg : *args) node->children.push_back(arg);
        delete args;
        node->children.push_back(*static_cast<ASTNodePtr*>($6));
        delete static_cast<ASTNodePtr*>($6);
        $$ = new ASTNodePtr(node);
    }
;


opt_args:
    /* empty */ { $$ = new ASTNodeList(); }
    | args      { $$ = $1; }
;

args:
    LET IDENTIFIER {
        auto list = new ASTNodeList();
        list->push_back(std::make_shared<ASTNode>(NodeType::Argument, std::string($2)));
        $$ = list;
    }
    | args COMMA LET IDENTIFIER {
        auto list = static_cast<ASTNodeList*>($1);
        list->push_back(std::make_shared<ASTNode>(NodeType::Argument, std::string($4)));
        $$ = list;
    }
;


return_stmt:
    RETURN expression {
        auto node = std::make_shared<ASTNode>(NodeType::Return);
        node->children.push_back(*static_cast<ASTNodePtr*>($2));
        delete static_cast<ASTNodePtr*>($2);
        $$ = new ASTNodePtr(node);
    }
;

if_stmt:
    IF LPAREN expression RPAREN block {
        auto node = std::make_shared<ASTNode>(NodeType::If);
        node->children.push_back(*static_cast<ASTNodePtr*>($3));
        node->children.push_back(*static_cast<ASTNodePtr*>($5));
        delete static_cast<ASTNodePtr*>($3);
        delete static_cast<ASTNodePtr*>($5);
        $$ = new ASTNodePtr(node);
    }
    | IF LPAREN expression RPAREN block ELSE block {
        auto node = std::make_shared<ASTNode>(NodeType::IfElse);
        node->children.push_back(*static_cast<ASTNodePtr*>($3));
        node->children.push_back(*static_cast<ASTNodePtr*>($5));
        node->children.push_back(*static_cast<ASTNodePtr*>($7));
        delete static_cast<ASTNodePtr*>($3);
        delete static_cast<ASTNodePtr*>($5);
        delete static_cast<ASTNodePtr*>($7);
        $$ = new ASTNodePtr(node);
    }
;

while_stmt:
    WHILE LPAREN expression RPAREN block {
        auto node = std::make_shared<ASTNode>(NodeType::While);
        node->children.push_back(*static_cast<ASTNodePtr*>($3)); // condition
        node->children.push_back(*static_cast<ASTNodePtr*>($5)); // body
        delete static_cast<ASTNodePtr*>($3);
        delete static_cast<ASTNodePtr*>($5);
        $$ = new ASTNodePtr(node);
    }
;


for_stmt:
    FOR LPAREN assignment SEMICOLON expression SEMICOLON assignment RPAREN block {
        auto node = std::make_shared<ASTNode>(NodeType::For);
        node->children.push_back(*static_cast<ASTNodePtr*>($3)); // init (assignment)
        node->children.push_back(*static_cast<ASTNodePtr*>($5)); // condition (expression)
        node->children.push_back(*static_cast<ASTNodePtr*>($7)); // update (assignment)
        node->children.push_back(*static_cast<ASTNodePtr*>($9)); // body (block)
        delete static_cast<ASTNodePtr*>($3);
        delete static_cast<ASTNodePtr*>($5);
        delete static_cast<ASTNodePtr*>($7);
        delete static_cast<ASTNodePtr*>($9);
        $$ = new ASTNodePtr(node);
    }
;



expression:
      INT_LITERAL      { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::IntLiteral, $1)); }
    | FLOAT_LITERAL    { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::FloatLiteral, $1)); }
    | STRING_LITERAL {
     std::string raw($1);
     if (!raw.empty() && raw.length() >= 2 && raw.front() == '"' && raw.back() == '"') {
        raw = raw.substr(1, raw.length() - 2);  // remove surrounding quotes
     }
     $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::StringLiteral, raw));
     free($1);  // since strdup() was used in lexer
    }
    | BOOLEAN_LITERAL  { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::BoolLiteral, $1)); }
    | IDENTIFIER {
        auto ident = std::make_shared<ASTNode>(NodeType::Identifier, std::string($1));
        // Try to get the type from symbol table, default to Int if not found
        auto symbol = symbolTable.lookup(std::string($1));
        if (symbol) {
            ident->valueType = symbol->type;
        }
        $$ = new ASTNodePtr(ident);
    }
    | expression PLUS expression {
        auto left = *static_cast<ASTNodePtr*>($1);
        auto right = *static_cast<ASTNodePtr*>($3);
        $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::BinaryOp, "+", left, right));
        delete static_cast<ASTNodePtr*>($1);
        delete static_cast<ASTNodePtr*>($3);
    }
    | expression MINUS expression { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::BinaryOp, "-", *static_cast<ASTNodePtr*>($1), *static_cast<ASTNodePtr*>($3))); delete static_cast<ASTNodePtr*>($1); delete static_cast<ASTNodePtr*>($3); }
    | expression MUL expression   { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::BinaryOp, "*", *static_cast<ASTNodePtr*>($1), *static_cast<ASTNodePtr*>($3))); delete static_cast<ASTNodePtr*>($1); delete static_cast<ASTNodePtr*>($3); }
    | expression DIV expression   { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::BinaryOp, "/", *static_cast<ASTNodePtr*>($1), *static_cast<ASTNodePtr*>($3))); delete static_cast<ASTNodePtr*>($1); delete static_cast<ASTNodePtr*>($3); }
    | expression LT expression    { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::BinaryOp, "<", *static_cast<ASTNodePtr*>($1), *static_cast<ASTNodePtr*>($3))); delete static_cast<ASTNodePtr*>($1); delete static_cast<ASTNodePtr*>($3); }
    | expression GT expression    { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::BinaryOp, ">", *static_cast<ASTNodePtr*>($1), *static_cast<ASTNodePtr*>($3))); delete static_cast<ASTNodePtr*>($1); delete static_cast<ASTNodePtr*>($3); }
    | expression EQ expression    { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::BinaryOp, "==", *static_cast<ASTNodePtr*>($1), *static_cast<ASTNodePtr*>($3))); delete static_cast<ASTNodePtr*>($1); delete static_cast<ASTNodePtr*>($3); }
    | expression NEQ expression   { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::BinaryOp, "!=", *static_cast<ASTNodePtr*>($1), *static_cast<ASTNodePtr*>($3))); delete static_cast<ASTNodePtr*>($1); delete static_cast<ASTNodePtr*>($3); }
    | expression LE expression    { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::BinaryOp, "<=", *static_cast<ASTNodePtr*>($1), *static_cast<ASTNodePtr*>($3))); delete static_cast<ASTNodePtr*>($1); delete static_cast<ASTNodePtr*>($3); }
    | expression GE expression    { $$ = new ASTNodePtr(std::make_shared<ASTNode>(NodeType::BinaryOp, ">=", *static_cast<ASTNodePtr*>($1), *static_cast<ASTNodePtr*>($3))); delete static_cast<ASTNodePtr*>($1); delete static_cast<ASTNodePtr*>($3); }
    | LPAREN expression RPAREN   { $$ = $2; }
    | call                         { $$ = $1; }  
;

opt_call_args:
    /* empty */ { $$ = new ASTNodeList(); }
    | call_args { $$ = $1; }
;

call_args:
    expression {
        auto list = new ASTNodeList();
        list->push_back(*static_cast<ASTNodePtr*>($1));
        delete static_cast<ASTNodePtr*>($1);
        $$ = list;
    }
    | call_args COMMA expression {
        auto list = static_cast<ASTNodeList*>($1);
        list->push_back(*static_cast<ASTNodePtr*>($3));
        delete static_cast<ASTNodePtr*>($3);
        $$ = list;
    }
;

call:
    IDENTIFIER LPAREN opt_call_args RPAREN {
        if (std::string($1) == "print") {
            reportError(ErrorType::SemanticError, "print() cannot be used as expression", yylineno);
            $$ = new ASTNodePtr(nullptr);
        } else {
            auto node = std::make_shared<ASTNode>(NodeType::FunctionCall, std::string($1));
            auto args = static_cast<ASTNodeList*>($3);
            for (auto& arg : *args) {
                node->children.push_back(arg);
            }
            delete args;
            $$ = new ASTNodePtr(node);
        }
    }
;

%%

int yyerror(const char* msg) {
    reportError(ErrorType::SyntaxError, msg, yylineno);
    return 0;
}
