# BasicCode Compiler

A simple and efficient compiler for the BasicCode (.bac) programming language, built using Flex, Bison, GCC, and CMake. This project compiles `.bac` source files into executable machine code.

## 🚀 Features

✅ **Lexical Analysis**: Tokenization using Flex for efficient source code scanning  
✅ **Syntax Parsing**: AST generation using Bison with comprehensive grammar support  
✅ **Code Generation**: Native machine code generation using GCC backend  
✅ **Expression Support**: Full support for arithmetic, logical, and comparison expressions  
✅ **Variable Management**: Declaration, assignment, and scope handling for variables  
✅ **Function Support**: Function definitions, calls, and parameter passing  
✅ **Symbol Table**: Efficient symbol table management for identifier resolution  
✅ **Error Handling**: Comprehensive error reporting with line numbers and context  
✅ **Custom IR**: Custom Intermediate Representation instead of LLVM for lighter footprint  
✅ **Cross-Platform**: Builds on Windows, Linux, and macOS

## 🛠️ Setting Up the Project

### 1️⃣ Install Dependencies

Make sure you have the following installed:

- **CMake** (version 3.10 or higher) → [Download](https://cmake.org/download/)
- **MSYS2** (for MinGW GCC on Windows) → [Download](https://www.msys2.org/)
- **Flex & Bison** → Install `WinFlexBison` from [here](https://sourceforge.net/projects/winflexbison/)

### 2️⃣ Install MinGW GCC on MSYS2

After installing MSYS2, open the MSYS2 MinGW64 terminal and run:

```sh
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-cmake
```

### 3️⃣ Install Flex & Bison (WinFlexBison)

- Download `WinFlexBison` from [SourceForge](https://sourceforge.net/projects/winflexbison/)
- Extract the folder and add it to your System PATH
- Verify installation:

```sh
win_flex --version
win_bison --version
```

## 🏗️ Building the Compiler

### 1️⃣ Clone the Repository

```sh
git clone https://github.com/yourusername/BasicCode-Compiler.git
cd BasicCode-Compiler
```

### 2️⃣ Configure & Build with CMake

```sh
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### 3️⃣ Run the Compiler

```sh
./mycompiler ../examples/test.bac
```

## 📂 Project Structure

```
BasicCode-Compiler/
├── include/                # Header files (.h)
│   ├── lexer.h            # Lexer definitions and token types
│   ├── parser.h           # Parser & AST structure definitions
│   ├── ast.h              # AST node types and transformations
│   ├── codegen.h          # Code generation logic
│   ├── symboltable.h      # Symbol table management
│   └── error.h            # Error handling utilities
│
├── src/                   # Source files
│   ├── lexer.l            # Flex lexer specification
│   ├── parser.y           # Bison parser grammar
│   ├── ast.cpp            # AST manipulation and optimization
│   ├── codegen.cpp        # Code generation (GCC backend)
│   ├── symboltable.cpp    # Symbol table implementation
│   ├── error.cpp          # Error handling implementation
│   └── main.cpp           # Compiler entry point
│
├── examples/              # Example .bac programs
│   ├── test.bac           # Basic arithmetic operations
│   ├── functions.bac      # Function definition examples
│   └── variables.bac      # Variable declaration examples
│
├── CMakeLists.txt         # Build configuration
└── README.md              # Project documentation
```

## 📜 Writing BasicCode (`.bac`) Programs

### Example Program

Create a file named `test.bac`:

```bac
// Variable declarations
let x = 10;
let y = 20;
let result = x + y;

// Function definition
function multiply(a, b) {
    return a * b;
}

// Function call and output
let product = multiply(x, y);
print("Sum:", result);
print("Product:", product);
```

### Compile and Run

```sh
./mycompiler examples/test.bac
./a.out
```

**Expected output:**

```
Sum: 30
Product: 200
```

## 🐛 Troubleshooting

### Common Issues and Solutions

**1️⃣ `CMake Error: No project() command`**  
👉 **Solution**: Ensure your `CMakeLists.txt` starts with:

```cmake
cmake_minimum_required(VERSION 3.10)
project(BasicCode-Compiler)
```

**2️⃣ `CMake cannot find Flex/Bison`**  
👉 **Solution**:

- Verify `win_flex.exe` and `win_bison.exe` are in your PATH
- Try reinstalling WinFlexBison and updating your PATH

**3️⃣ `GCC Not Found`**  
👉 **Solution**: Install GCC through MSYS2:

```sh
pacman -S mingw-w64-x86_64-gcc
```

**4️⃣ `Permission Denied` when running executable**  
👉 **Solution**:

- On Windows: Check antivirus software
- On Linux/macOS: Ensure executable permissions with `chmod +x ./mycompiler`

## 🤝 Contributing

We welcome contributions! Here's how you can help:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Development Guidelines

- Follow existing code style and conventions
- Update documentation as needed

## 👥 Contributors

- **Shailesh Singh Bisht** – Project Lead & Maintainer
- **Nitin Rawat** – Lexer + Error Handler Implementation
- **Akhil Nautiyal** – AST + Error Handler Implementation
- **Vivek Pokhriyal** – Parser + Symbol Table Implementation

Want to contribute? We'd love to have you! Check out our Contributing Guidelines and submit a Pull Request! 🎉

## 📄 License

This project is licensed under the **MIT License** - see the `LICENSE` file for details.

## 🚀 Roadmap

- [ ] Implement standard library functions
- [ ] Add debugging information generation
- [ ] Create IDE/editor plugins
- [ ] Implement optimization passes

## 📞 Support

If you encounter any issues or have questions:

- Open an issue on GitHub
- Check the documentation in the `docs/` folder
- Join our discussions in the GitHub Discussions tab

**Happy Coding with BasicCode!** 🎯
