#include "../include/symboltable.h"

using namespace std;

// Stores information about a symbol (variable or function) including its type and scope level
SymbolInfo::SymbolInfo(const string &name, VarType type, SymbolType symbolType, int scopeLevel)
    : name(name), type(type), symbolType(symbolType), scopeLevel(scopeLevel) {}

// Initialize symbol table with global scope (scope level 0)
SymbolTable::SymbolTable()
{
    scopes.emplace_back();
}

// Create new scope for blocks (if, while, functions, etc.)
void SymbolTable::enterScope()
{
    ++currentScope;
    scopes.emplace_back();
}

// Exit current scope and remove all symbols in it
void SymbolTable::exitScope()
{
    if (currentScope > 0)
    {
        scopes.pop_back();
        --currentScope;
    }
}

// Declare a new symbol in current scope
// Returns false if symbol already exists in current scope
bool SymbolTable::declare(const string &name, VarType type, SymbolType symbolType)
{
    auto &current = scopes.back();
    if (current.count(name) > 0)
        return false;

    current[name] = make_shared<SymbolInfo>(name, type, symbolType, currentScope);
    return true;
}

// Look up a symbol in current and outer scopes
// Searches from innermost to outermost scope
// Returns nullptr if symbol not found
shared_ptr<SymbolInfo> SymbolTable::lookup(const string &name)
{
    for (int i = currentScope; i >= 0; --i)
    {
        auto &scope = scopes[i];
        if (scope.count(name))
            return scope[name];
    }
    return nullptr;
}
