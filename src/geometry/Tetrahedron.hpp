#pragma once

#include "geometry/Vertex.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>

namespace tetra {

using TetrahedronId = std::size_t;
using Face = std::array<VertexId, 3>;

// 只保存连接关系：四个数字表示四面体连接哪四个 Mesh 顶点。
// 坐标仍由 Mesh 中的 Vertex 保存，避免在每个单元中复制坐标。
struct Tetrahedron {
    std::array<VertexId, 4> vertices{};

    [[nodiscard]] VertexId vertex(std::size_t local_index) const
    {
        return vertices.at(local_index);
    }

    [[nodiscard]] bool contains_vertex(VertexId id) const
    {
        return std::find(vertices.begin(), vertices.end(), id) != vertices.end();
    }

    // 返回与 local_index 对面的三角面。
    // 当四个顶点已经被 orient3d 排列为正向时，返回面的方向朝向单元外部。
    [[nodiscard]] Face face_opposite(std::size_t local_index) const
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

