#pragma once

// FindBadTetrahedra.hpp 声明“寻找坏四面体”的函数。
// 这里的“坏”表示新点进入了该四面体的外接球。

#include "geometry/Mesh.hpp"

#include <vector>

namespace tetra {

// mesh 是当前网格，point 是准备插入的新点。
// 返回值保存所有需要删除的四面体编号。
std::vector<TetrahedronId> find_bad_tetrahedra(const Mesh& mesh, Vec3 point);

} // namespace tetra
