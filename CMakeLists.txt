cmake_minimum_required(VERSION 3.15)
project(BasicCodeCompiler)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

# Manually set WinFlexBison paths
set(FLEX_EXECUTABLE "C:/WinFlexBison/win_flex.exe")
set(BISON_EXECUTABLE "C:/WinFlexBison/win_bison.exe")

# Find Flex and Bison
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Flex & Bison targets
FLEX_TARGET(Lexer
    ${PROJECT_SOURCE_DIR}/src/lexer.l
    ${CMAKE_BINARY_DIR}/lexer.cpp
)

BISON_TARGET(Parser
    ${PROJECT_SOURCE_DIR}/src/parser.y
    ${CMAKE_BINARY_DIR}/parser.cpp
    DEFINES_FILE ${CMAKE_BINARY_DIR}/parser.tab.h
)

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

# Sources
set(SOURCES
    src/main.cpp
    src/ast.cpp
    src/codegen.cpp
    src/error.cpp
    src/symboltable.cpp
    ${FLEX_Lexer_OUTPUTS}
    ${BISON_Parser_OUTPUTS}
)

# Includes
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}  # Needed for parser.tab.h
)

# Executable
add_executable(mycompiler ${SOURCES})
