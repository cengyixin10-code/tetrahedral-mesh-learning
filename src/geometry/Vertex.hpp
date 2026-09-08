#pragma once

#include "geometry/Vec3.hpp"

#include <cstddef>

namespace tetra {

// V0.1 中，顶点编号始终等于它在 Mesh 顶点数组中的位置。
using VertexId = std::size_t;

struct Vertex {
    VertexId id{};
    Vec3 position{};
};

} // namespace tetra

