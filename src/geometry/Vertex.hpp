#pragma once

// Vertex.hpp 把“几何坐标”和“网格中的身份编号”组合成一个顶点。

#include "geometry/Vec3.hpp"

#include <cstddef>

namespace tetra {

// VertexId 是顶点编号的类型。
// 它本质上是非负整数，但单独起名后，代码能明确表达“这是顶点编号”。
// V0.1 中，编号始终等于顶点在 Mesh 顶点数组中的位置。
using VertexId = std::size_t;

struct Vertex {
    // id 用于四面体保存连接关系。建立后不应随意改变。
    VertexId id{};

    // position 保存这个顶点在三维空间中的实际坐标。
    Vec3 position{};
};

} // namespace tetra

