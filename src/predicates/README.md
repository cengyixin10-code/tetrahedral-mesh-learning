# 几何判断模块

## V0.1-5 orient3d：已实现，尚未添加测试

`Orientation.hpp` 声明函数，`Orientation.cpp` 实现计算。

计算过程：

```text
ab = b - a
ac = c - a
ad = d - a

orient3d = (ab × ac) · ad
```

`ab × ac` 是平面 `abc` 的法向量。它与 `ad` 的点积为正或为负，说明 `d` 位于平面的不同侧；结果为零表示四点共面。绝对值是四面体体积的 6 倍。

当前版本直接使用 `double`，目的是先看清算法。它还不是 TetGen 使用的自适应精确几何判断：点非常接近共面时，浮点舍入可能让符号不可靠。这个问题在基础 Bowyer-Watson 跑通后再单独处理。

下一步 `InSphere.hpp/.cpp` 将判断一个点位于四面体外接球的内部、外部还是球面上。

`examples/orient3d_demo.cpp` 给定四个简单坐标，打印 `orient3d` 返回值和四面体体积。它用于观察计算结果，没有复杂的自动断言。
