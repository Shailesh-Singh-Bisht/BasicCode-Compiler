#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <string>
#include <memory>
#include <ostream>

// Responsible for converting AST into C code
class CodeGenerator {
public:
    CodeGenerator();

    // Generate C code from the root AST and write to file
    void generate(const std::shared_ptr<ASTNode>& root, const std::string& outputFile);

private:
    void generateNode(const std::shared_ptr<ASTNode>& node, std::ostream& out);
    void generateStatement(const std::shared_ptr<ASTNode>& node, std::ostream& out);
    void generateExpression(const std::shared_ptr<ASTNode>& node, std::ostream& out);
};

#endif // CODEGEN_H
