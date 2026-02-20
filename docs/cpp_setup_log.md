# C++ 环境搭建与运行记录

## 任务概述
在 Linux 环境下创建并运行一个简单的 C++ 程序。

## 步骤记录

### 1. 创建 C++ 源文件

**文件名**: `hello.cpp`

**内容**:
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

**说明**: 一个简单的 Hello World 程序，使用 C++ 标准库输出文本。

---

### 2. 首次编译尝试

**命令**:
```bash
g++ hello.cpp -o hello && ./hello
```

**结果**: 失败
```
/bin/bash: g++: command not found
```

**问题**: 系统未安装 g++ 编译器。

---

### 3. 安装 g++ 编译器

**命令**:
```bash
sudo apt update && sudo apt install -y g++
```

**安装过程**:
- 更新软件包列表
- 安装以下包：
  - `g++` (4:9.3.0-1ubuntu2)
  - `g++-9` (9.4.0-1ubuntu1~20.04.2)
  - `libstdc++-9-dev` (9.4.0-1ubuntu1~20.04.2)
- 下载大小: 10.1 MB
- 安装后占用: 46.8 MB

**结果**: 安装成功

---

### 4. 编译 C++ 程序

**命令**:
```bash
g++ hello.cpp -o hello
```

**参数说明**:
- `g++`: C++ 编译器
- `hello.cpp`: 源文件
- `-o hello`: 指定输出可执行文件名为 `hello`

**结果**: 编译成功，生成可执行文件 `hello`

---

### 5. 运行程序

**命令**:
```bash
./hello
```

**输出**:
```
Hello, World!
```

**结果**: 程序运行成功

---

## 环境信息

- **操作系统**: Linux 5.4.0-216-generic
- **平台**: Ubuntu 20.04 LTS (Focal)
- **编译器**: g++ 9.4.0
- **工作目录**: /home/ubuntu/jyy_os

---

## 总结

从零开始在 Linux 环境下运行 C++ 程序需要：

1. 编写 C++ 源代码文件 (.cpp)
2. 确保 g++ 编译器已安装（如未安装需通过 apt 安装）
3. 使用 g++ 编译源代码生成可执行文件
4. 运行生成的可执行文件

整个过程顺利完成，最终成功运行 Hello World 程序。
