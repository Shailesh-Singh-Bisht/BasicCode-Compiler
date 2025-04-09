#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "ast.h"  // For VarType

// Types of entries that can be stored in the symbol table
enum class SymbolType {
    Variable,
    Function
};

// Information for each declared symbol
struct SymbolInfo {
    std::string name;
    VarType type;
    SymbolType symbolType;
    int scopeLevel;

    SymbolInfo(const std::string& name, VarType type, SymbolType symbolType, int scopeLevel);
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
    bool declare(const std::string& name, VarType type, SymbolType symbolType);

    // Look up a symbol by name, searching from innermost to outermost scope
    std::shared_ptr<SymbolInfo> lookup(const std::string& name);

private:
    int currentScope = 0;
    std::vector<std::unordered_map<std::string, std::shared_ptr<SymbolInfo>>> scopes;
};

#endif // SYMBOLTABLE_H
