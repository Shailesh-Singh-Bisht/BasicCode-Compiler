#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "ast.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <filesystem>

using namespace std;

extern int yyparse();
extern FILE *yyin;
extern shared_ptr<ASTNode> root;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <source.bac>\n";
        return EXIT_FAILURE;
    }

    // Setup input and output paths
    const char *inputFile = argv[1];
    filesystem::path inputPath(inputFile);
    string baseFilename = inputPath.stem().string();

    // Verify file extension
    string fname = inputFile;
    if (fname.size() < 4 || fname.substr(fname.size() - 4) != ".bac")
    {
        cerr << "⚠️  Warning: Input file doesn't end in '.bac'\n";
    }

    // Open and verify input file
    yyin = fopen(inputFile, "r");
    if (!yyin)
    {
        cerr << "❌ Error: Could not open file " << inputFile << "\n";
        return EXIT_FAILURE;
    }

    cout << "🔍 Parsing " << inputFile << "...\n";

    // Parse input and generate code if successful
    if (yyparse() == 0 && root)
    {
        // Setup output directory structure
        filesystem::path exePath = filesystem::path(argv[0]);
        filesystem::path projectDir = exePath.parent_path().parent_path();
        filesystem::path outputDir = projectDir / "output";
        filesystem::create_directory(outputDir);

        // Define output files
        string outputFile = (outputDir / (baseFilename + ".c")).string();
        string outputExe = (outputDir / (baseFilename + ".exe")).string();

        // Generate C code
        cout << "\n🚧 --- Generating Code ---\n";
        CodeGenerator codegen;
        codegen.generate(root, outputFile);
        cout << "✅ Output written to `" << outputFile << "`\n";

        // Compile and run the generated code
        cout << "\n🚧 --- Compiling and Running ---\n";
        string compileCmd = "gcc \"" + outputFile + "\" -o \"" + outputExe + "\"";
        string runCmd = "\"" + outputExe + "\"";
        system((compileCmd + " && " + runCmd).c_str());
    }
    else
    {
        cerr << "❌ Parsing failed. Check syntax errors above.\n";
        fclose(yyin);
        return EXIT_FAILURE;
    }

    fclose(yyin);
    return EXIT_SUCCESS;
}
