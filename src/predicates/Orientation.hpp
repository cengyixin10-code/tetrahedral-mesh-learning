#pragma once

// Orientation.hpp 声明 orient3d 函数。
// 它回答的问题是：点 d 位于有方向的平面 abc 的哪一侧？

#include "geometry/Vec3.hpp"

namespace tetra {

// 返回值大于 0：d 位于 abc 法向量所指的一侧。
// 返回值小于 0：d 位于另一侧。
// 返回值等于 0：四个点共面。
// 返回值的绝对值等于四面体体积的 6 倍。
double orient3d(Vec3 a, Vec3 b, Vec3 c, Vec3 d);

} // namespace tetra
