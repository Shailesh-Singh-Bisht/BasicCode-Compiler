cmake_minimum_required(VERSION 3.15)
project(BasicCodeCompiler)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Flex & Bison
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Define source files
FLEX_TARGET(Lexer src/lexer.l ${CMAKE_BINARY_DIR}/lexer.cpp)
BISON_TARGET(Parser src/parser.y ${CMAKE_BINARY_DIR}/parser.cpp)

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

# Compiler setup
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

# Source files
set(SOURCES
    src/main.cpp
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Lexer_OUTPUTS}
    src/ast.cpp
    src/codegen.cpp
)

# Include directories
include_directories(${CMAKE_BINARY_DIR} include)

# Define executable
add_executable(mycompiler ${SOURCES})

# Link necessary libraries
target_link_libraries(mycompiler stdc++)
