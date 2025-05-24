#include "../include/error.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// Tracks total number of errors encountered during compilation
static int errorCount = 0;

// Reports compilation errors with type, message, and line number
// Exits after 10 errors to prevent error cascade
void reportError(ErrorType type, const string &message, int line)
{
    cerr << "[Error";

    // Format error type for output
    switch (type)
    {
    case ErrorType::SyntaxError:
        cerr << " - Syntax";
        break;
    case ErrorType::SemanticError:
        cerr << " - Semantic";
        break;
    case ErrorType::RuntimeError:
        cerr << " - Runtime";
        break;
    }

    // Add line number if available
    if (line >= 0)
        cerr << "] Line " << line << ": ";
    else
        cerr << "]: ";

    cerr << message << endl;

    ++errorCount;

    // Stop compilation if too many errors occur
    if (errorCount >= 10)
    {
        cerr << "[Error] Too many errors. Compilation aborted." << endl;
        exit(EXIT_FAILURE);
    }
}

// Returns total number of errors encountered
int getErrorCount()
{
    return errorCount;
}

// Resets the error counter, useful between compilation units
void resetErrorCount()
{
    errorCount = 0;
}
