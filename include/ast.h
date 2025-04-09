#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

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
std::string nodeTypeToString(NodeType type);

class ASTNode {
public:
    NodeType type;
    VarType valueType = VarType::Int;

    int intVal = 0;
    float floatVal = 0.0f;
    bool boolVal = false;
    std::string strVal;

    std::shared_ptr<ASTNode> left = nullptr;
    std::shared_ptr<ASTNode> right = nullptr;
    std::vector<std::shared_ptr<ASTNode>> children;

    // Constructors
    explicit ASTNode(NodeType type);
    ASTNode(NodeType type, int value);
    ASTNode(NodeType type, float value);
    ASTNode(NodeType type, bool value);
    ASTNode(NodeType type, const std::string& value);
    ASTNode(NodeType type, const std::string& op, std::shared_ptr<ASTNode> lhs, std::shared_ptr<ASTNode> rhs);
    ASTNode(NodeType type, const std::vector<std::shared_ptr<ASTNode>>& children);

    // Utilities
    void print(int indent = 0) const;
    std::string getLiteralAsString() const;
};

#endif // AST_H
