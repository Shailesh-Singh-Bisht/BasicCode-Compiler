#include "../include/error.h"
#include <iostream>
#include <cstdlib>

static int errorCount = 0;

void reportError(ErrorType type, const std::string& message, int line) {
    std::cerr << "[Error";

    switch (type) {
        case ErrorType::SyntaxError:   std::cerr << " - Syntax";   break;
        case ErrorType::SemanticError: std::cerr << " - Semantic"; break;
        case ErrorType::RuntimeError:  std::cerr << " - Runtime";  break;
    }

    if (line >= 0)
        std::cerr << "] Line " << line << ": ";
    else
        std::cerr << "]: ";

    std::cerr << message << std::endl;

    ++errorCount;

    // Limit to prevent endless error spam
    if (errorCount >= 10) {
        std::cerr << "[Error] Too many errors. Compilation aborted." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

int getErrorCount() {
    return errorCount;
}

void resetErrorCount() {
    errorCount = 0;
}
