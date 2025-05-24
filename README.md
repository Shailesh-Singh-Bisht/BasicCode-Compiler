# BasicCode Compiler
<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
[![All Contributors](https://img.shields.io/badge/all_contributors-4-orange.svg?style=flat-square)](#contributors-)
<!-- ALL-CONTRIBUTORS-BADGE:END -->

A simple and efficient compiler for the BasicCode (.bac) programming language, built using Flex, Bison, GCC, and CMake. This project compiles `.bac` source files into executable machine code for Windows.

## 🚀 Features

✅ **Lexical Analysis**: Tokenization using Flex for efficient source code scanning  
✅ **Syntax Parsing**: AST generation using Bison with comprehensive grammar support  
✅ **Code Generation**: C Code generation by traversing the AST.  
✅ **Expression Support**: Full support for arithmetic, logical, and comparison expressions  
✅ **Variable Management**: Declaration, assignment, and scope handling for variables  
✅ **Function Support**: Function definitions, calls, and parameter passing  
✅ **Symbol Table**: Efficient symbol table management for identifier resolution  
✅ **Error Handling**: Comprehensive error reporting with line numbers and context  
✅ **Windows Compatible**: Built specifically for Windows systems  

## 🏃‍♂️ Quick Start - Using Pre-built Binaries

> **Want to try BasicCode immediately?** Skip the build process and use our pre-compiled binaries!

### 📥 Download & Setup

1. **Download the Release Package**
   - Go to our [Releases page](https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler/releases/tag/Release)
   - Download the latest `BasicCode-Compiler.rar` for Windows

2. **Extract & Install**
   ```cmd
   # Extract to your desired location (e.g., C:\BasicCode-Compiler)
   ```

### 🔧 Configure System PATH

**Option 1: GUI Method**
1. **Open Environment Variables**
   - Press `Win + R`, type `sysdm.cpl`, press Enter
   - Click "Environment Variables..." button

2. **Edit PATH Variable**
   - Under "System variables", find and select `Path`
   - Click "Edit..." → "New"
   - Add: `C:\BasicCode-Compiler\bin` (or your extraction path)
   - Click "OK" to save all changes

**Option 2: Command Line Method**
```cmd
# Run as Administrator
setx PATH "%PATH%;C:\BasicCode-Compiler\bin" /M
```

### 🎯 Usage Examples

```cmd
# Compile a BasicCode file
mycompiler hello.bac

# Compile with output specification
mycompiler input.bac -o myprogram.exe
```

---

## 🛠️ Building From Source

### 1️⃣ Install Dependencies

**Windows (MSYS2):**
```bash
# Install MSYS2 from https://www.msys2.org/
# Then run in MSYS2 MinGW64 terminal:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-cmake

# Install WinFlexBison from https://sourceforge.net/projects/winflexbison/
```

### 2️⃣ Clone & Build

```bash
git clone https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler.git
cd BasicCode-Compiler

# Create build directory
mkdir build && cd build

# Configure and build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### 3️⃣ Test Your Build

```bash
# Test the compiled binary
./mycompiler.exe ../examples/test.bac
```

## 📂 Project Structure

```
BasicCode-Compiler/
├── 📁 include/                # Header files (.h)
│   ├── lexer.h               # Lexer definitions and token types
│   ├── parser.h              # Parser & AST structure definitions
│   ├── ast.h                 # AST node types and transformations
│   ├── codegen.h             # Code generation logic
│   ├── symboltable.h         # Symbol table management
│   └── error.h               # Error handling utilities
│
├── 📁 src/                   # Source files
│   ├── lexer.l               # Flex lexer specification
│   ├── parser.y              # Bison parser grammar
│   ├── ast.cpp               # AST manipulation and optimization
│   ├── codegen.cpp           # Code generation (GCC backend)
│   ├── symboltable.cpp       # Symbol table implementation
│   ├── error.cpp             # Error handling implementation
│   └── main.cpp              # Compiler entry point
│
├── 📁 examples/              # Example .bac programs
│   ├── test.bac              # Basic arithmetic operations
│   ├── functions.bac         # Function definition examples
│   └── variables.bac         # Variable declaration examples
├── CMakeLists.txt            # Build configuration
└── README.md                 # This file
```

## 📜 Writing BasicCode (`.bac`) Programs

### Basic Syntax Example

Create a file named `hello.bac`:

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

// Conditional statements
if (result > 25) {
    print("Result is greater than 25");
} else {
    print("Result is 25 or less");
}

// Loops
for (let i = 1; i <= 5; i = i + 1) {
    print("Iteration:", i);
}
```

### Compile and Run

```cmd
mycompiler hello.bac
```

**Expected Output:**
```
Sum: 30
Product: 200
Result is greater than 25
Iteration: 1
Iteration: 2
Iteration: 3
Iteration: 4
Iteration: 5
```

## 🐛 Troubleshooting

### Common Issues and Solutions

| Issue | Solution |
|-------|----------|
| **`mycompiler` command not found** | Verify PATH is correctly set and restart command prompt |
| **`CMake Error: No project() command`** | Ensure `CMakeLists.txt` starts with proper project declaration |
| **`CMake cannot find Flex/Bison`** | Install WinFlexBison and add to PATH |
| **`GCC Not Found`** | Install GCC via MSYS2 |
| **Access denied on executable** | Run command prompt as Administrator |

## 🤝 Contributing

We welcome contributions! Here's how you can help:

### Quick Start for Contributors

1. **Fork & Clone**
   ```bash
   git clone https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler.git
   cd BasicCode-Compiler
   ```

2. **Create Feature Branch**
   ```bash
   git checkout -b feature/amazing-feature
   ```

3. **Make Changes & Test**
   ```bash
   # Build and test your changes
   mkdir build && cd build
   cmake .. && cmake --build .
   ```

4. **Submit Pull Request**
   ```bash
   git commit -m "Add amazing feature"
   git push origin feature/amazing-feature
   ```

### Development Guidelines

- Follow existing code style and conventions
- Add tests for new features
- Update documentation as needed
- Ensure Windows compatibility

## 📄 License

This project is licensed under the **MIT License** - see the `LICENSE` file for details.

## 🗺️ Roadmap

- [ ] **IDE Integration**: Create plugins for VS Code, Vim, etc.
- [ ] **Optimization**: Implement compiler optimization passes
- [ ] **Package Manager**: Create a package management system

## 📞 Support & Community

- 🐛 **Bug Reports**: [Open an Issue](https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler/issues)
- 📖 **Documentation**: Coming in few days
- 🆘 **Help**: Tag us in issues with `help wanted` label

## Contributors ✨

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tbody>
    <tr>
      <td align="center" valign="top" width="14.28%"><a href="https://shailesh-singh-bisht-portfolio.vercel.app/"><img src="https://avatars.githubusercontent.com/u/107263955?v=4?s=100" width="100px;" alt="Shailesh Singh Bisht"/><br /><sub><b>Shailesh Singh Bisht</b></sub></a><br /><a href="#projectManagement-Shailesh-Singh-Bisht" title="Project Management">📆</a> <a href="#maintenance-Shailesh-Singh-Bisht" title="Maintenance">🚧</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/royalhub123"><img src="https://avatars.githubusercontent.com/u/168981505?v=4?s=100" width="100px;" alt="royalhub123"/><br /><sub><b>royalhub123</b></sub></a><br /><a href="https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler/commits?author=royalhub123" title="Code">💻</a> <a href="#tool-royalhub123" title="Tools">🔧</a> <a href="https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler/issues?q=author%3Aroyalhub123" title="Bug reports">🐛</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/Akhilnautiyal5"><img src="https://avatars.githubusercontent.com/u/113812781?v=4?s=100" width="100px;" alt="Akhil Nautiyal"/><br /><sub><b>Akhil Nautiyal</b></sub></a><br /><a href="https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler/commits?author=Akhilnautiyal5" title="Code">💻</a> <a href="https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler/commits?author=Akhilnautiyal5" title="Tests">⚠️</a> <a href="https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler/issues?q=author%3AAkhilnautiyal5" title="Bug reports">🐛</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/Vivek-Pokhriyal"><img src="https://avatars.githubusercontent.com/u/202429019?v=4?s=100" width="100px;" alt="Vivek-Pokhriyal"/><br /><sub><b>Vivek-Pokhriyal</b></sub></a><br /><a href="https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler/commits?author=Vivek-Pokhriyal" title="Code">💻</a> <a href="https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler/pulls?q=is%3Apr+reviewed-by%3AVivek-Pokhriyal" title="Reviewed Pull Requests">👀</a> <a href="https://github.com/Shailesh-Singh-Bisht/BasicCode-Compiler/commits?author=Vivek-Pokhriyal" title="Tests">⚠️</a></td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <td align="center" size="13px" colspan="7">
        <img src="https://raw.githubusercontent.com/all-contributors/all-contributors-cli/1b8533af435da9854653492b1327a23a4dbd0a10/assets/logo-small.svg">
          <a href="https://all-contributors.js.org/docs/en/bot/usage">Add your contributions</a>
        </img>
      </td>
    </tr>
  </tfoot>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

Want to contribute? We'd love to have you! Check out our [Contributing Guidelines](#-contributing) and submit a Pull Request! 🎉

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!

---

**Happy Coding with BasicCode!** 🎯
