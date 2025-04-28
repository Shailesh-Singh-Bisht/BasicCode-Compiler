#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

enum class NodeType {
    Program,
    Block,
    Declaration,
    Assignment,
    Function,
    Argument,
    Return,
    If,
    IfElse,
    While,
    For,
    BinaryOp,
    UnaryOp,
    Identifier,
    IntLiteral,
    FloatLiteral,
    BoolLiteral,
    StringLiteral,
    FunctionCall
};

enum class VarType {
    Int,
    Float,
    Bool,
    String,
    Void
};

// Convert NodeType to string (for debugging/printing)
string nodeTypeToString(NodeType type);

class ASTNode {
public:
    NodeType type;
    VarType valueType = VarType::Int;

    int intVal = 0;
    float floatVal = 0.0f;
    bool boolVal = false;
    string strVal;

    shared_ptr<ASTNode> left = nullptr;
    shared_ptr<ASTNode> right = nullptr;
    vector<shared_ptr<ASTNode>> children;

    // Constructors
    explicit ASTNode(NodeType type);
    ASTNode(NodeType type, int value);
    ASTNode(NodeType type, float value);
    ASTNode(NodeType type, bool value);
    ASTNode(NodeType type, const string& value);
    ASTNode(NodeType type, const string& op, shared_ptr<ASTNode> lhs, shared_ptr<ASTNode> rhs);
    ASTNode(NodeType type, const vector<shared_ptr<ASTNode>>& children);

    // Utilities
    void print(int indent = 0) const;
    string getLiteralAsString() const;
};

#endif // AST_H
