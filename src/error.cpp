#include "../include/error.h"
#include <iostream>
#include <cstdlib>
using namespace std;

static int errorCount = 0;

void reportError(ErrorType type, const string& message, int line) {
    cerr << "[Error";

    switch (type) {
        case ErrorType::SyntaxError:   cerr << " - Syntax";   break;
        case ErrorType::SemanticError: cerr << " - Semantic"; break;
        case ErrorType::RuntimeError:  cerr << " - Runtime";  break;
    }

    if (line >= 0)
        cerr << "] Line " << line << ": ";
    else
        cerr << "]: ";

    cerr << message << endl;

    ++errorCount;
    
    if (errorCount >= 10) {
        cerr << "[Error] Too many errors. Compilation aborted." << endl;
        exit(EXIT_FAILURE);
    }
}

int getErrorCount() {
    return errorCount;
}

void resetErrorCount() {
    errorCount = 0;
}
