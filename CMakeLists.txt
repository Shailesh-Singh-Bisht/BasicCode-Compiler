cmake_minimum_required(VERSION 3.15)
project(BasicCodeCompiler)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Manually set compilers if using MSYS2
# Only do this if you're running CMake from outside MSYS2
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

# Find Flex & Bison
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Flex & Bison targets
FLEX_TARGET(Lexer src/lexer.l ${CMAKE_BINARY_DIR}/lexer.cpp)
BISON_TARGET(Parser src/parser.y ${CMAKE_BINARY_DIR}/parser.cpp)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

# Source files
set(SOURCES
    src/main.cpp
    src/ast.cpp
    src/codegen.cpp
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Lexer_OUTPUTS}
)

# Headers
include_directories(${CMAKE_BINARY_DIR} include)

# Executable
add_executable(mycompiler ${SOURCES})

# This line is not necessary:
# target_link_libraries(mycompiler stdc++) 
# C++ linking is handled automatically by CMake.
