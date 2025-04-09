#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "ast.h"

#include <iostream>
#include <fstream>
#include <memory>

// External Flex/Bison interfaces
extern int yyparse();
extern FILE* yyin;

// Root of AST from parser
extern std::shared_ptr<ASTNode> root;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source.bac>\n";
        return EXIT_FAILURE;
    }

    const char* inputFile = argv[1];
    yyin = fopen(inputFile, "r");
    if (!yyin) {
        std::cerr << " Error: Could not open file " << inputFile << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "🔍 Parsing " << inputFile << "...\n";

    if (yyparse() == 0 && root) {
        std::cout << "\n✅ --- AST ---\n";
        root->print();

        std::cout << "\n --- Generating Code ---\n";
        CodeGenerator codegen;
        codegen.generate(root, "output.c");

        std::cout << "✅ Output written to `output.c`\n";
    } else {
        std::cerr << "❌ Parsing failed. Check syntax errors above.\n";
    }

    fclose(yyin);
    return EXIT_SUCCESS;
}
