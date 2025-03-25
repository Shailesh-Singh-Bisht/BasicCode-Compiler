Here is your **`README_DEV.md`** for developers contributing to the **BasicCode Compiler** project.  

---

# **🛠️ BasicCode Compiler – Developer Guide**  

This guide is for **developers contributing to the BasicCode Compiler**. It covers project setup, code structure, debugging, and contribution guidelines.  

---

## **📂 Project Structure**  
```
📂 BasicCodeCompiler
│── 📂 build/          # Compiled binaries (ignored in Git)
│── 📂 include/        # Header files (.h)
│── 📂 src/            # Source files (.cpp)
│── 📂 tests/          # Unit tests
│── 📂 examples/       # Sample programs in BasicCode
│── .gitignore         # Ignore unnecessary files
│── CMakeLists.txt     # CMake build configuration
│── README.md          # User guide (users see this)
│── README_DEV.md      # Developer guide (this file)
│── CONTRIBUTING.md    # Contribution guidelines
```

---

## **🔧 Setting Up Development Environment**  
### **1️⃣ Clone the Repository**  
```bash
git clone https://github.com/yourusername/BasicCodeCompiler.git
cd BasicCodeCompiler
```

### **2️⃣ Install Dependencies**  
#### **Windows (MSYS2 MinGW)**  
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja
```
#### **Linux/macOS**  
```bash
sudo apt install g++ cmake ninja-build
```

### **3️⃣ Build the Project**  
```bash
mkdir build && cd build
cmake .. -G "Ninja"
ninja
```

---

## **🛠️ Code Structure**  
### **1️⃣ Lexer (`lexer.cpp`)**  
- Reads **BasicCode source code** and **tokenizes** it.  
- Uses **regular expressions or a manual tokenizer**.  

### **2️⃣ Parser (`parser.cpp`)**  
- Converts **tokens into an Abstract Syntax Tree (AST)**.  
- Uses a **recursive descent parser** or **LR parsing**.  

### **3️⃣ Code Generator (`codegen.cpp`)**  
- Converts the AST into **C code** or **assembly code**.  

### **4️⃣ MinGW-w64 GCC (`mingw32-make`)**  
- Compiles the generated C file into an executable.  

---

## **🔄 Debugging**  
### **1️⃣ Enable Debug Mode in CMake**  
Modify **CMakeLists.txt** to include:  
```cmake
set(CMAKE_BUILD_TYPE Debug)
```

### **2️⃣ Run Debugger**  
```bash
gdb build/compiler.exe
```
Inside GDB:  
```gdb
break main
run
next
```

---

## **✅ Contributing**  
### **1️⃣ Fork the Repository**  
Go to **GitHub**, click **Fork** on the repository page.  

### **2️⃣ Create a Feature Branch**  
```bash
git checkout -b feature-name
```

### **3️⃣ Write Code & Add Comments**  

### **4️⃣ Run Tests**  
```bash
cd tests
./run_tests.sh
```

### **5️⃣ Commit & Push**  
```bash
git commit -m "Added new feature"
git push origin feature-name
```

### **6️⃣ Open a Pull Request** 🚀  

---

## **📜 License**  
This project is **open-source** under the **MIT License**.  

---

# **✅ Developer Guide Ready! 🚀**  
Now, developers can use this **README_DEV.md** for project setup, debugging, and contributing.  

Let me know if you need any refinements! 😊