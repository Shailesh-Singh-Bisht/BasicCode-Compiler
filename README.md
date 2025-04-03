Here’s a **developer-friendly `README.md`** for your **BasicCode** compiler project. It includes setup instructions, project structure, and usage details. 🚀  

---

### **📜 `README.md` for BasicCode Compiler**  

```md
# BasicCode Compiler  
A simple compiler for the **BasicCode (`.bac`)** programming language, built using **Flex, Bison, GCC, and CMake**. This project compiles `.bac` source files into executable machine code.  

## 🚀 Features  
✅ **Lexical Analysis** (Tokenization using Flex)  
✅ **Parsing & AST Generation** (Using Bison)  
✅ **Code Generation** (Using GCC backend)  
✅ **Support for Expressions, Variables, and Functions**  
✅ **Custom Intermediate Representation (IR) instead of LLVM**  

---

## 🛠️ Setting Up the Project  

### **1️⃣ Install Dependencies**  
Make sure you have the following installed:  

🔹 **CMake** → [Download](https://cmake.org/download/)  
🔹 **MSYS2 (for MinGW GCC)** → [Download](https://www.msys2.org/)  
🔹 **Flex & Bison** → Install `WinFlexBison` from [here](https://sourceforge.net/projects/winflexbison/)  

### **2️⃣ Install MinGW GCC on MSYS2**  
After installing MSYS2, open the **MSYS2 MinGW64 terminal** and run:  
```sh
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make
```

### **3️⃣ Install Flex & Bison (WinFlexBison)**  
- Download `WinFlexBison` from [SourceForge](https://sourceforge.net/projects/winflexbison/)  
- Extract it, and add the `bin/` directory to your **System PATH**.  

Check installation with:  
```sh
win_flex --version
win_bison --version
```

---

## 🏗️ Building the Compiler  

### **1️⃣ Clone the Repository**  
```sh
git clone https://github.com/yourusername/BasicCode-Compiler.git
cd BasicCode-Compiler
```

### **2️⃣ Configure & Build with CMake**  
```sh
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### **3️⃣ Run the Compiler**  
```sh
./mycompiler ../examples/test.bac
```

---

## 📂 Project Structure  

```
BasicCode-Compiler/
│── include/               # Header files (.h)
│   ├── lexer.h            # Lexer definitions
│   ├── parser.h           # Parser & AST structure
│   ├── ast.h              # AST optimizations & transformations
│   ├── codegen.h          # Code generation logic
│
│── src/                   # Source files (.cpp)
│   ├── lexer.l            # Flex (Lexer)
│   ├── parser.y           # Bison (Parser)
│   ├── ast.cpp            # AST manipulation
│   ├── codegen.cpp        # Code generation (GCC backend)
│   ├── main.cpp           # Compiler entry point
│
│── examples/              # Example .bac programs
│   ├── test.bac           # Sample BasicCode program
│
│── tests/                 # Test cases
│
│── CMakeLists.txt         # Build configuration
│── README.md              # Project documentation
```

---

## 📜 Writing a BasicCode (`.bac`) Program  
Example **`test.bac`** file:  
```bac
let x = 10;
let y = 20;
let result = x + y;
print(result);
```

To compile it:  
```sh
./mycompiler examples/test.bac -o test.exe
./test.exe
```

---

## 🔧 Troubleshooting  

### **1️⃣ `CMake Error: No project() command`**
👉 Edit `CMakeLists.txt` and add this at the top:  
```cmake
cmake_minimum_required(VERSION 3.10)
project(BasicCode-Compiler)
```

### **2️⃣ `CMake cannot find Flex/Bison`**
👉 Make sure `win_flex.exe` and `win_bison.exe` are in your PATH.  

### **3️⃣ `GCC Not Found`**
👉 Run this inside MSYS2 terminal:  
```sh
pacman -S mingw-w64-x86_64-gcc
```

---

## 🏆 Contributors  
👤 **Your Name** – Creator & Maintainer  

📢 Want to contribute? Feel free to submit a **Pull Request!** 🎉  

---

## 📜 License  
This project is **open-source** under the **MIT License**.  

```

---

### **🔥 Next Steps**
- **✅ Review this `README.md`** to ensure it fits your project.  
- **✅ Push your project to GitHub.**  
- **✅ Add example `.bac` programs** in the `examples/` folder.  
- **✅ Share the repo with your dev friends!**  

Let me know if you need modifications. 🚀