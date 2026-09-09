#pragma once

// InSphere.hpp 声明 inSphere 函数。
// 它用来判断点 e 与四面体 abcd 的外接球之间的位置关系。

#include "geometry/Vec3.hpp"

namespace tetra {

// 使用这个函数前，先用 orient3d(a, b, c, d) 确认四面体方向。
// 当 orient3d 的结果大于 0 时：
//   返回值大于 0：e 在外接球内部。
//   返回值小于 0：e 在外接球外部。
//   返回值等于 0：e 在外接球表面。
double inSphere(Vec3 a, Vec3 b, Vec3 c, Vec3 d, Vec3 e);

} // namespace tetra
