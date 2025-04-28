#include "../include/symboltable.h"

using namespace std;

SymbolInfo::SymbolInfo(const string& name, VarType type, SymbolType symbolType, int scopeLevel)
    : name(name), type(type), symbolType(symbolType), scopeLevel(scopeLevel) {}

SymbolTable::SymbolTable() {
    scopes.emplace_back();
}

void SymbolTable::enterScope() {
    ++currentScope;
    scopes.emplace_back();
}

void SymbolTable::exitScope() {
    if (currentScope > 0) {
        scopes.pop_back();
        --currentScope;
    }
}

bool SymbolTable::declare(const string& name, VarType type, SymbolType symbolType) {
    auto& current = scopes.back();
    if (current.count(name) > 0)
        return false;

    current[name] = make_shared<SymbolInfo>(name, type, symbolType, currentScope);
    return true;
}

shared_ptr<SymbolInfo> SymbolTable::lookup(const string& name) {

    for (int i = currentScope; i >= 0; --i) {
        auto& scope = scopes[i];
        if (scope.count(name))
            return scope[name];
    }
    return nullptr;
}
