#pragma once

// Tetrahedron.hpp 定义四面体的拓扑连接关系。
// 它不重复保存坐标，只保存“连接了哪四个顶点”。

#include "geometry/Vertex.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>

namespace tetra {

// TetrahedronId 是四面体在 Mesh 中的稳定编号。
using TetrahedronId = std::size_t;

// 一个三角面由三个顶点编号组成。
using Face = std::array<VertexId, 3>;

struct Tetrahedron {
    // vertices[0] 到 vertices[3] 是四面体的四个“局部顶点”。
    // 数组中保存的是全局 VertexId，需要通过 Mesh 才能取得实际坐标。
    std::array<VertexId, 4> vertices{};

    // 根据局部编号 0、1、2、3 取得对应的全局 VertexId。
    // at() 会检查范围；错误地传入 4 或更大的数时会报告异常。
    VertexId vertex(std::size_t local_index) const
    {
        return vertices.at(local_index);
    }

    // 检查这个四面体的四个顶点中是否存在指定的全局编号。
    bool contains_vertex(VertexId id) const
    {
        return std::find(vertices.begin(), vertices.end(), id) != vertices.end();
    }

    // 四面体的每个顶点都有一个不包含该顶点的“对面”。
    // 例如 local_index=0 时，对面由 vertices[1]、[2]、[3] 组成。
    // 当四面体顶点已由 orient3d 调整为正向时，这里的排列会让面朝向单元外部。
    // 这个方向会在后续提取 Cavity 边界和重新四面体化时发挥作用。
    Face face_opposite(std::size_t local_index) const
    {
        switch (local_index) {
        case 0: return {vertices[1], vertices[2], vertices[3]};
        case 1: return {vertices[0], vertices[3], vertices[2]};
        case 2: return {vertices[0], vertices[1], vertices[3]};
        case 3: return {vertices[0], vertices[2], vertices[1]};
        default: throw std::out_of_range("A tetrahedron has exactly four local vertices.");
        }
    }
};

} // namespace tetra

