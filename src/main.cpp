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
        std::cerr << "Usage: " << argv[0] << " <source.bac> [output.c]\n";
        return EXIT_FAILURE;
    }

    const char* inputFile = argv[1];
    std::string outputFile = (argc >= 3) ? argv[2] : "output.c";

    // Optional: warn if file isn't .bac
    std::string fname = inputFile;
    if (fname.size() < 4 || fname.substr(fname.size() - 4) != ".bac") {
        std::cerr << "⚠️  Warning: Input file doesn't end in '.bac'\n";
    }

    yyin = fopen(inputFile, "r");
    if (!yyin) {
        std::cerr << "❌ Error: Could not open file " << inputFile << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "🔍 Parsing " << inputFile << "...\n";

    if (yyparse() == 0 && root) {
        std::cout << "\n✅ --- AST ---\n";
        root->print();

        std::cout << "\n🚧 --- Generating Code ---\n";
        CodeGenerator codegen;
        codegen.generate(root, outputFile);

        std::cout << "✅ Output written to `" << outputFile << "`\n";
    } else {
        std::cerr << "❌ Parsing failed. Check syntax errors above.\n";
        fclose(yyin);
        return EXIT_FAILURE;
    }

    fclose(yyin);
    return EXIT_SUCCESS;
}
