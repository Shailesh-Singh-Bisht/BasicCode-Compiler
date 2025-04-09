#include "ast.h"
#include <iostream>

ASTNode::ASTNode(NodeType type) : type(type) {}

ASTNode::ASTNode(NodeType type, int value)
    : type(type), intVal(value), valueType(VarType::Int) {}

ASTNode::ASTNode(NodeType type, float value)
    : type(type), floatVal(value), valueType(VarType::Float) {}

ASTNode::ASTNode(NodeType type, bool value)
    : type(type), boolVal(value), valueType(VarType::Bool) {}

ASTNode::ASTNode(NodeType type, const std::string &value)
    : type(type), strVal(value) {
        std::cerr << "[AST DEBUG] String constructor: " << value << "\n";
    }

ASTNode::ASTNode(NodeType type, const std::string &op,
                 std::shared_ptr<ASTNode> lhs, std::shared_ptr<ASTNode> rhs)
    : type(type), strVal(op), left(std::move(lhs)), right(std::move(rhs)) {}

ASTNode::ASTNode(NodeType type, const std::vector<std::shared_ptr<ASTNode>> &children)
    : type(type), children(children) {}

std::string nodeTypeToString(NodeType type)
{
    switch (type)
    {
    case NodeType::Program:
        return "Program";
    case NodeType::Block:
        return "Block";
    case NodeType::Declaration:
        return "Declaration";
    case NodeType::Assignment:
        return "Assignment";
    case NodeType::Function:
        return "Function";
    case NodeType::Argument:
        return "Argument";
    case NodeType::Return:
        return "Return";
    case NodeType::If:
        return "If";
    case NodeType::IfElse:
        return "IfElse";
    case NodeType::While:
        return "While";
    case NodeType::For:
        return "For";
    case NodeType::BinaryOp:
        return "BinaryOp";
    case NodeType::UnaryOp:
        return "UnaryOp";
    case NodeType::Identifier:
        return "Identifier";
    case NodeType::IntLiteral:
        return "IntLiteral";
    case NodeType::FloatLiteral:
        return "FloatLiteral";
    case NodeType::BoolLiteral:
        return "BoolLiteral";
    case NodeType::StringLiteral:
        return "StringLiteral";
    case NodeType::FunctionCall:
        return "FunctionCall";
    default:
        return "Unknown";
    }
}

void ASTNode::print(int indent) const
{
    for (int i = 0; i < indent; ++i)
        std::cout << "  ";
    std::cout << nodeTypeToString(type);

    switch (type)
    {
    case NodeType::Identifier:
    case NodeType::StringLiteral:
    case NodeType::FunctionCall:
    case NodeType::BinaryOp:
    case NodeType::UnaryOp:
    case NodeType::Argument:
    case NodeType::Declaration:
    case NodeType::Assignment:
    case NodeType::Function:
        if (!strVal.empty())
            std::cout << " = " << strVal;
        break;

    case NodeType::IntLiteral:
        std::cout << " = " << intVal;
        break;

    case NodeType::FloatLiteral:
        std::cout << " = " << floatVal;
        break;

    case NodeType::BoolLiteral:
        std::cout << " = " << (boolVal ? "true" : "false");
        break;

    default:
        break;
    }

    std::cout << '\n';

    if (left)
        left->print(indent + 1);
    if (right)
        right->print(indent + 1);

    for (const auto &child : children)
    {
        if (child)
            child->print(indent + 1);
    }
}
