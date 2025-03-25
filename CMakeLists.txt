cmake_minimum_required(VERSION 3.10)
project(BasicCodeCompiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use MinGW-w64 GCC from MSYS2
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

# Add source files
add_executable(compiler 
    src/main.cpp 
    src/lexer.cpp 
    src/parser.cpp 
    src/ast.cpp 
    src/codegen.cpp
)
