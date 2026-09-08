# TetGen 参考材料

本仓库不包含 TetGen 源码。这样可以把教学代码的版本历史与 TetGen 的第三方授权和源码历史分开。

如需同时编译本地 TetGen 演示目标，请在此目录运行：

```powershell
git clone --branch v1.6.0 --depth 1 https://github.com/TetGen/TetGen.git tetgen
```

之后执行项目根目录的 `build-and-test.ps1`。CMake 会自动检测 `reference/tetgen`：存在时编译 `tetgen_cli` 和 `tetgen_smoke`；不存在时只编译本项目的教学代码。

来源：https://github.com/TetGen/TetGen

TetGen v1.6.0 的授权采用 AGPLv3 / 商业双重许可。使用其代码或发布包含它的程序前，应阅读其 `LICENSE` 并确认适用授权。
