Here’s a **user-friendly README** for people who want to use your **BasicCode Compiler**.  

---

# **🚀 BasicCode Compiler**  
A simple compiler for the **BasicCode** programming language, built using **C++ and MinGW-w64**.  

## **📌 Features**
✅ Supports **variable declarations, loops, and functions**  
✅ Converts **BasicCode** into C code or Assembly  
✅ Works on **Windows (MSYS2 MinGW)**  
✅ Open-source and easy to use  

---

## **📥 Installation**
### **🔹 Prerequisites**
Before using the compiler, install:  
- ✅ **MSYS2 with MinGW-w64** (Download: [https://www.msys2.org/](https://www.msys2.org/))  
- ✅ **CMake** (Download: [https://cmake.org/download/](https://cmake.org/download/))  
- ✅ **GCC/G++** (Installed via MSYS2)  

### **🔹 Cloning the Repository**
```bash
git clone https://github.com/yourusername/BasicCodeCompiler.git
cd BasicCodeCompiler
```

---

## **🛠️ How to Build the Compiler**
### **🔹 Step 1: Configure the Build**
```bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
```

### **🔹 Step 2: Compile the Compiler**
```bash
mingw32-make
```

### **🔹 Step 3: Verify the Compiler**
Run:
```bash
./compiler --help
```
If it prints usage instructions, your compiler is ready! ✅  

---

## **🚀 Running BasicCode Programs**
### **🔹 Compiling a BasicCode File**
To compile a `.bac` file, run:
```bash
./compiler ../examples/hello.bac -o output.c
```
This generates `output.c`, which you can compile using **GCC**:
```bash
gcc output.c -o program.exe
```
Run the program:
```bash
./program.exe
```

---

## **📜 Example: BasicCode Program (`hello.bac`)**
```basiccode
print("Hello, World!");
```
### **✅ Compiling & Running**
```bash
./compiler hello.bac -o hello.c
gcc hello.c -o hello.exe
./hello.exe
```

---

## **📝 Supported BasicCode Syntax**
### **🔹 Variables**
```basiccode
int x = 10;
float y = 5.5;
```
### **🔹 Conditionals**
```basiccode
if (x > 0) {
   print("Positive Number");
} else {
   print("Negative Number");
}
```
### **🔹 Loops**
```basiccode
for (int i = 0; i < 5; i++) {
   print(i);
}
```
### **🔹 Functions**
```basiccode
func sum(int a, int b) -> int {
   return a + b;
}

int result = sum(5, 10);
print(result);
```

---

## **❓ Troubleshooting**
| **Problem**                 | **Solution** |
|-----------------------------|-------------|
| `compiler: command not found` | Make sure the build was successful (`mingw32-make`). |
| `gcc: error: output.c: No such file or directory` | Ensure `compiler` is generating C code correctly. |

---

## **📌 Contributing**
Want to improve the compiler? Follow these steps:  
1. **Fork the repository**  
2. **Create a new branch** (`git checkout -b feature-name`)  
3. **Make changes & commit** (`git commit -m "Added new feature"`)  
4. **Push changes** (`git push origin feature-name`)  
5. **Create a pull request** 🚀  

---

## **📜 License**
This project is **open-source** under the **MIT License**.  

---

# **🎯 Now Your Compiler is Ready for Users! 🚀**
This README is **simple, structured, and easy to follow** for users who want to **compile and run BasicCode programs**.  

Next, do you need a **README for developers contributing to the project?** 😊