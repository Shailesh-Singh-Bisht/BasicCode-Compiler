// Abstract Syntax Tree (AST) implementation
#include "ast.h"
#include <iostream>

using namespace std;

// Basic constructor for nodes that don't have values
ASTNode::ASTNode(NodeType type) : type(type) {}

// Constructor for integer value nodes
ASTNode::ASTNode(NodeType type, int value)
    : type(type), intVal(value), valueType(VarType::Int) {}

// Constructor for float value nodes
ASTNode::ASTNode(NodeType type, float value)
    : type(type), floatVal(value), valueType(VarType::Float) {}

// Constructor for boolean value nodes
ASTNode::ASTNode(NodeType type, bool value)
    : type(type), boolVal(value), valueType(VarType::Bool) {}

// Constructor for string value nodes and declarations
ASTNode::ASTNode(NodeType type, const string &value)
    : type(type), strVal(value)
{
    // For declarations, set the value type based on the child node
    if (type == NodeType::Declaration && !children.empty())
    {
        valueType = children[0]->valueType;
    }
}

// Constructor for binary operations (operations with left and right operands)
ASTNode::ASTNode(NodeType type, const string &op,
                 shared_ptr<ASTNode> lhs, shared_ptr<ASTNode> rhs)
    : type(type), strVal(op), left(move(lhs)), right(move(rhs)) {}

// Constructor for nodes that have multiple children (like blocks or function bodies)
ASTNode::ASTNode(NodeType type, const vector<shared_ptr<ASTNode>> &children)
    : type(type), children(children) {}

// Converts node types to their string representation
string nodeTypeToString(NodeType type)
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
