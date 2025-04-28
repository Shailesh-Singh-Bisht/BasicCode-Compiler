#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "ast.h"  // For VarType

using namespace std;

// Types of entries that can be stored in the symbol table
enum class SymbolType {
    Variable,
    Function
};

// Information for each declared symbol
struct SymbolInfo {
    string name;
    VarType type;
    SymbolType symbolType;
    int scopeLevel;

    SymbolInfo(const string& name, VarType type, SymbolType symbolType, int scopeLevel);
};

// SymbolTable with nested scopes
class SymbolTable {
public:
    SymbolTable();

    // Enter a new nested scope
    void enterScope();

    // Exit the current scope
    void exitScope();

    // Declare a new symbol in the current scope
    bool declare(const string& name, VarType type, SymbolType symbolType);

    // Look up a symbol by name, searching from innermost to outermost scope
    shared_ptr<SymbolInfo> lookup(const string& name);

private:
    int currentScope = 0;
    vector<unordered_map<string, shared_ptr<SymbolInfo>>> scopes;
};

#endif // SYMBOLTABLE_H
