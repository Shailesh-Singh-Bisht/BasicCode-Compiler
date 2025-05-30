#include "codegen.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Code generator class for translating AST to C code
CodeGenerator::CodeGenerator() {}

// Main generation function - creates C file with necessary includes
void CodeGenerator::generate(const shared_ptr<ASTNode> &root, const string &outputFile)
{
    ofstream out(outputFile);
    if (!out.is_open())
    {
        cerr << "Failed to open output file: " << outputFile << '\n';
        return;
    }

    out << "#include <stdio.h>\n\n";
    generateNode(root, out);
    out.close();
}

// Handles program and block nodes by generating their child statements
void CodeGenerator::generateNode(const shared_ptr<ASTNode> &node, ostream &out)
{
    if (!node)
        return;

    if (node->type == NodeType::Program || node->type == NodeType::Block)
    {
        for (const auto &child : node->children)
        {
            generateStatement(child, out);
        }
    }
    else
    {
        generateStatement(node, out);
    }
}

// Generates C code for different types of statements (if, while, for, etc.)
void CodeGenerator::generateStatement(const shared_ptr<ASTNode> &node, ostream &out)
{
    if (!node)
        return;
    bool firstParam = true;

    switch (node->type)
    {
    // Variable declarations with initialization
    case NodeType::Declaration:
        if (node->children[0]->type == NodeType::FloatLiteral)
        {
            out << "float ";
        }
        else
        {
            out << "int ";
        }
        out << node->strVal << " = ";
        generateExpression(node->children[0], out);
        out << ";\n";
        break;

    // Variable assignments
    case NodeType::Assignment:
        out << node->strVal << " = ";
        generateExpression(node->children[0], out);
        out << ";\n";
        break;

    // Return statements with optional value
    case NodeType::Return:
        out << "return ";
        if (!node->children.empty())
        {
            generateExpression(node->children[0], out);
        }
        out << ";\n";
        break;

    // Control flow statements
    case NodeType::If:
        out << "if (";
        generateExpression(node->children[0], out);
        out << ") ";
        generateStatement(node->children[1], out);
        break;

    case NodeType::IfElse:
        out << "if (";
        generateExpression(node->children[0], out);
        out << ") ";
        generateStatement(node->children[1], out);
        out << " else ";
        generateStatement(node->children[2], out);
        break;

    case NodeType::While:
        out << "while (";
        generateExpression(node->children[0], out);
        out << ") ";
        generateStatement(node->children[1], out);
        break;

    case NodeType::For:
        out << "for (";
        if (node->children[0]->type == NodeType::Declaration)
        {
            out << "int " << node->children[0]->strVal << " = ";
            generateExpression(node->children[0]->children[0], out);
        }
        else
        {
            out << node->children[0]->strVal << " = ";
            generateExpression(node->children[0]->children[0], out);
        }
        out << "; ";
        generateExpression(node->children[1], out);
        out << "; ";
        generateExpression(node->children[2], out);
        out << ") ";
        generateStatement(node->children[3], out);
        break;

    // Function definitions with type handling
    case NodeType::Function:
    {
        switch (node->valueType)
        {
        case VarType::Float:
            out << "float ";
            break;
        case VarType::Int:
            out << "int ";
            break;
        case VarType::Bool:
            out << "int ";
            break;
        case VarType::String:
            out << "const char* ";
            break;
        default:
            out << "void ";
            break;
        }

        out << node->strVal << "(";
        firstParam = true;
        for (const auto &child : node->children)
        {
            if (child->type == NodeType::Argument)
            {
                if (!firstParam)
                    out << ", ";
                firstParam = false;

                switch (child->valueType)
                {
                case VarType::Float:
                    out << "float ";
                    break;
                case VarType::Int:
                    out << "int ";
                    break;
                case VarType::Bool:
                    out << "int ";
                    break;
                case VarType::String:
                    out << "const char* ";
                    break;
                default:
                    out << "int ";
                    break;
                }
                out << child->strVal;
            }
        }
        out << ") ";

        for (const auto &child : node->children)
        {
            if (child->type == NodeType::Block)
                generateStatement(child, out);
        }
        break;
    }

    // Code blocks with proper bracing
    case NodeType::Block:
        out << "{\n";
        for (const auto &stmt : node->children)
            generateStatement(stmt, out);
        out << "}\n";
        break;

    // Function calls with special handling for print function
    case NodeType::FunctionCall:
        if (node->strVal == "print")
        {
            const auto &arg = node->children[0];

            switch (arg->type)
            {
            case NodeType::StringLiteral:
                out << "printf(\"%s\", ";
                break;
            case NodeType::FloatLiteral:
            case NodeType::Identifier:
                if (arg->valueType == VarType::Float)
                {
                    out << "printf(\"%f\", ";
                }
                else
                {
                    out << "printf(\"%d\", ";
                }
                break;
            case NodeType::BoolLiteral:
                out << "printf(\"%s\", ";
                break;
            default:
                out << "printf(\"%d\", ";
                break;
            }
            generateExpression(arg, out);
            out << ");\n";
        }
        else
        {
            out << node->strVal << "(";
            for (size_t i = 0; i < node->children.size(); ++i)
            {
                generateExpression(node->children[i], out);
                if (i + 1 < node->children.size())
                    out << ", ";
            }
            out << ")";
        }
        break;

    default:
        out << "\n";
        break;
    }
}

// Generates C code for expressions (literals, operations, function calls)
void CodeGenerator::generateExpression(const shared_ptr<ASTNode> &node, ostream &out)
{
    if (!node)
        return;

    switch (node->type)
    {
    // Basic expressions
    case NodeType::Assignment:
        out << node->strVal << " = ";
        generateExpression(node->children[0], out);
        break;

    // Literal values
    case NodeType::IntLiteral:
        out << node->intVal;
        break;

    case NodeType::FloatLiteral:
        out << node->floatVal;
        break;

    case NodeType::BoolLiteral:
        out << (node->strVal == "true" ? "1" : "0");
        break;

    case NodeType::StringLiteral:
        out << "\"" << node->strVal << "\"";
        break;

    // Variable references
    case NodeType::Identifier:
        out << node->strVal;
        break;

    // Binary operations with parentheses for precedence
    case NodeType::BinaryOp:
        out << "(";
        generateExpression(node->left, out);
        out << " " << node->strVal << " ";
        generateExpression(node->right, out);
        out << ")";
        break;

    // Unary operations
    case NodeType::UnaryOp:
        out << node->strVal;
        generateExpression(node->children[0], out);
        break;

    // Function calls in expressions
    case NodeType::FunctionCall:
        if (node->strVal == "print")
        {
            out << "/* print() used as expression — invalid */";
        }
        else
        {
            out << node->strVal << "(";
            for (size_t i = 0; i < node->children.size(); ++i)
            {
                generateExpression(node->children[i], out);
                if (i + 1 < node->children.size())
                    out << ", ";
            }
            out << ")\n";
        }
        break;

    default:
        out << "/* unknown expr */";
        break;
    }
}
