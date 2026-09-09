# 四面体网格 C++ 学习项目

## 现在从哪里开始

先完成环境验证，再学习 examples/hello_world.cpp。你确认理解后，再逐个实现 src 中的模块。
目前五个算法模块只有职责说明；examples/tetgen_smoke.cpp 是安装验收示例，不是教学进度，也不是自行实现的算法。

## 工具分别做什么

| 工具 | 用途 |
|---|---|
| VS Code | 打开文件、编写代码、显示错误提示 |
| MSVC（Build Tools 内） | 把 C++ 代码翻译成 Windows 可执行程序 |
| Windows SDK | 提供构建 Windows 程序所需的系统头文件和库 |
| CMake | 按 CMakeLists.txt 组织编译工作 |
| Git | 保存版本、获取参考源码 |
| Ninja | 可选的构建执行工具，本项目使用 MSBuild，不依赖它 |

TetGen 的基础功能只需要 C++ 编译器和标准库。本项目直接编译 tetgen.cxx、predicates.cxx 并包含 tetgen.h，不需要先装 Boost、Eigen、CGAL、Qt 或 Python。STEP/IGES 读取、曲面离散、可视化不在这个最小项目内，待学习需要明确后再增加相应工具。

## 验证方式

安装完成后，在此目录打开 PowerShell，执行：

```powershell
powershell -ExecutionPolicy Bypass -File .\build-and-test.ps1
```

这里的执行策略参数只用于本次脚本进程，不修改系统执行策略。脚本自动寻找 CMake。输出在 build 目录。

构建目标：hello_world.exe（基础输出）、tetgen_cli.exe（原版命令行网格器）、tetgen_reference.lib（静态库）、tetgen_smoke.exe（调用静态库）。验收用四个不共面的点检查是否生成一个四面体及合法的连接索引，不代表复杂 CAD 已经验证。

## 第一课：先读 5 个概念

打开 examples/hello_world.cpp：

1. `#include <iostream>`：引入标准库的输出工具，就像先拿到工具箱。
2. `int main()`：定义程序的入口。`main` 是名字，`int` 表示它结束时会返回整数。
3. `{` 与 `}`：把属于这个函数的语句包起来。
4. `std::cout << "Hello, tetrahedral mesh!\n";`：向屏幕输出文字；`\n` 换行，分号结束语句。
5. `return 0;`：结束函数，并告诉系统程序正常完成。

以 `//` 开头的是给人看的注释，不会作为指令执行。`.cpp` 通常放实现；之后的 `.hpp` 通常放类型定义与函数声明。现在不必背熟。

## 后续模块顺序（等你的命令再写）

| 顺序 | 目录 | 要解决的问题 | 先学的 C++ |
|---|---|---|---|
| 1 | src/geometry | 一个点、一个四面体如何存到内存中 | 变量、double、struct、vector |
| 2 | src/io | 如何读入点、保存结果 | 函数、循环、文件读写 |
| 3 | src/predicates | 点在面的哪边、是否位于外接球内 | 参数、返回值、条件判断 |
| 4 | src/meshing | 如何逐点建立 Delaunay 四面体 | 容器、索引、算法流程 |
| 5 | src/quality | 结果有没有退化、连接错误 | 检查、误差、测试 |

## 当前学习进度

| 阶段 | 状态 | 你要验证的内容 |
|---|---|---|
| V0.1-1 Vec3 | 已实现，等待你测试 | 向量代数、右手定则、标量三重积 |
| V0.1-2 Vertex | 已实现 | 点编号与坐标 |
| V0.1-3 Tetrahedron | 已实现 | 四个顶点和四个面 |
| V0.1-4 Mesh | 已实现 | 存储、稳定编号和失效标记 |
| V0.1-5 orient3d | 已实现，尚未测试 | 有向体积和点位于平面的哪一侧 |

基础点集算法之后才讨论：封闭表面、边界恢复、内部区域提取、质量细化和优化。仅对点集做 Delaunay 会填充其凸包，不会自动识别凹形实体或孔洞。

学习目标是理解并逐步实现算法；参考 TetGen 和直接调用 TetGen 是两条不同的练习路径，这里都保留了入口。

## 参考源码

- 可信镜像：https://github.com/TetGen/TetGen
- 主开发仓库：https://codeberg.org/TetGen/TetGen
- 本地目录：reference/tetgen（不随本仓库提交；获取方式见 reference/README.md）
- 固定版本：v1.6.0
- 提交：535f9c41f44abc832a7bbf2c9c7af003d1c18f3c
- 原始源码保持不变，现代 CMake/MSVC 的构建规则写在本项目顶层。
- 授权文件保留在 reference/tetgen/LICENSE（AGPLv3 / 商业双重许可说明）。

安装和实际验证状态请看 ENVIRONMENT.md；以其中记录为准，不能把“准备好了构建文件”理解为“编译已经通过”。

