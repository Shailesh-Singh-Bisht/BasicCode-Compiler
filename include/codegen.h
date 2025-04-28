#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <string>
#include <memory>
#include <ostream>

using namespace std;

// Responsible for converting AST into C code
class CodeGenerator {
public:
    CodeGenerator();

    // Generate C code from the root AST and write to file
    void generate(const shared_ptr<ASTNode>& root, const string& outputFile);

private:
    void generateNode(const shared_ptr<ASTNode>& node, ostream& out);
    void generateStatement(const shared_ptr<ASTNode>& node, ostream& out);
    void generateExpression(const shared_ptr<ASTNode>& node, ostream& out);
};

#endif // CODEGEN_H
