#pragma once

// SuperTetrahedron.hpp 声明“创建超级四面体”的函数。
// 超级四面体是 Bowyer-Watson 算法开始时的第一个四面体。

#include "geometry/Vec3.hpp"

#include <array>
#include <vector>

namespace tetra {

// 根据输入点的范围，返回一个能够包住全部输入点的大四面体。
std::array<Vec3, 4> create_super_tetrahedron(std::vector<Vec3> points);

} // namespace tetra
