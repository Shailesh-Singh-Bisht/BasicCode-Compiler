#ifndef ERROR_H
#define ERROR_H

#include <string>

// Enum for error types
enum class ErrorType {
    SyntaxError,
    SemanticError,
    RuntimeError
};

// Report a compiler error with type, message, and optional line number
void reportError(ErrorType type, const std::string& message, int line = -1);

// Get number of errors encountered so far
int getErrorCount();

// Reset error count (useful in tests or multi-pass compilers)
void resetErrorCount();

#endif // ERROR_H
