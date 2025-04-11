#include "codegen.h"
#include <fstream>
#include <iostream>

CodeGenerator::CodeGenerator() {}

void CodeGenerator::generate(const std::shared_ptr<ASTNode> &root, const std::string &outputFile)
{
    std::ofstream out(outputFile);
    if (!out.is_open())
    {
        std::cerr << "Failed to open output file: " << outputFile << '\n';
        return;
    }

    out << "#include <stdio.h>\n\n";
    generateNode(root, out);
    out.close();
}

void CodeGenerator::generateNode(const std::shared_ptr<ASTNode> &node, std::ostream &out)
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

void CodeGenerator::generateStatement(const std::shared_ptr<ASTNode> &node, std::ostream &out)
{
    if (!node)
        return;

        std::cerr << "Generating Statement for: " << nodeTypeToString(node->type) << " = " << node->strVal << "\n";


    switch (node->type)
    {
    case NodeType::Declaration:
        out << "int " << node->strVal << " = ";
        generateExpression(node->children[0], out);
        out << ";\n";
        break;

    case NodeType::Assignment:
        out << node->strVal << " = ";
        generateExpression(node->children[0], out);
        out << ";\n";
        break;

    case NodeType::Return:
        out << "return ";
        if (!node->children.empty())
            generateExpression(node->children[0], out);
        out << ";\n";
        break;

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

    case NodeType::Function:
        out << "int " << node->strVal << "() ";
        for (const auto &child : node->children)
        {
            if (child->type == NodeType::Block)
                generateStatement(child, out);
        }
        break;

    case NodeType::Block:
        out << "{\n";
        for (const auto &stmt : node->children)
            generateStatement(stmt, out);
        out << "}\n";
        break;

    case NodeType::FunctionCall:
        if (node->strVal == "print")
        {
            std::cerr << "[CODEGEN DEBUG] Generating print() with arg type: " 
            << nodeTypeToString(node->children[0]->type) << "\n";
            std::cerr << "print() raw child strVal: " << node->children[0]->strVal << "\n";
            const auto &arg = node->children[0];
            switch (arg->type)
            {
            case NodeType::StringLiteral:
                out << "printf(\"%s\", ";
                break;
            case NodeType::FloatLiteral:
                out << "printf(\"%f\", ";
                break;
            case NodeType::BoolLiteral:
                out << "printf(\"%s\", ";
                break;
            case NodeType::IntLiteral:
            case NodeType::Identifier:
            case NodeType::BinaryOp:
                out << "printf(\"%d\", ";
                break;
            default:
                out << "printf(\"<unsupported>\", ";
                break;
            }
            generateExpression(arg, out);
            out << ");\n";
        }
        else
        {
            generateExpression(node, out);
            out << ";\n";
        }
        break;

    default:
        out << "/* Unhandled statement */\n";
        break;
    }
}

void CodeGenerator::generateExpression(const std::shared_ptr<ASTNode> &node, std::ostream &out)
{
    if (!node) return;

    switch (node->type)
    {
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

    case NodeType::Identifier:
        out << node->strVal;
        break;

    case NodeType::BinaryOp:
        out << "(";
        generateExpression(node->left, out);
        out << " " << node->strVal << " ";
        generateExpression(node->right, out);
        out << ")";
        break;

    case NodeType::UnaryOp:
        out << node->strVal;
        generateExpression(node->children[0], out);
        break;

    case NodeType::FunctionCall:
        if (node->strVal == "print") {
            out << "/* print() used as expression — invalid */";
        } else {
            out << node->strVal << "(";
            for (size_t i = 0; i < node->children.size(); ++i) {
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
