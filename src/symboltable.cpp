#include "../include/symboltable.h"

SymbolInfo::SymbolInfo(const std::string& name, VarType type, SymbolType symbolType, int scopeLevel)
    : name(name), type(type), symbolType(symbolType), scopeLevel(scopeLevel) {}

SymbolTable::SymbolTable() {
    // Initialize with global scope (level 0)
    scopes.emplace_back();
}

void SymbolTable::enterScope() {
    ++currentScope;
    scopes.emplace_back();
}

void SymbolTable::exitScope() {
    // Prevent popping below global scope
    if (currentScope > 0) {
        scopes.pop_back();
        --currentScope;
    }
}

bool SymbolTable::declare(const std::string& name, VarType type, SymbolType symbolType) {
    auto& current = scopes.back();
    
    // Return false if already declared in the current scope
    if (current.count(name) > 0)
        return false;

    current[name] = std::make_shared<SymbolInfo>(name, type, symbolType, currentScope);
    return true;
}

std::shared_ptr<SymbolInfo> SymbolTable::lookup(const std::string& name) {
    // Search from innermost to outermost scope
    for (int i = currentScope; i >= 0; --i) {
        auto& scope = scopes[i];
        if (scope.count(name))
            return scope[name];
    }
    return nullptr;
}
