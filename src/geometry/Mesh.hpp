#pragma once

#include "geometry/Tetrahedron.hpp"

#include <array>
#include <cstddef>
#include <vector>

namespace tetra {

// Mesh 是算法唯一拥有数据的对象。
// Bowyer-Watson 不立即擦除空腔四面体，而是把它们标记为 inactive。
// 这样旧编号保持稳定，遍历时不会因 vector 删除元素而失效。
class Mesh {
public:
    [[nodiscard]] VertexId add_vertex(Vec3 position);
    [[nodiscard]] TetrahedronId add_tetrahedron(std::array<VertexId, 4> vertices);

    [[nodiscard]] const Vertex& vertex(VertexId id) const;
    [[nodiscard]] const Tetrahedron& tetrahedron(TetrahedronId id) const;

    [[nodiscard]] bool is_active(TetrahedronId id) const;
    void deactivate_tetrahedron(TetrahedronId id);

    [[nodiscard]] std::vector<TetrahedronId> active_tetrahedron_ids() const;

    [[nodiscard]] std::size_t vertex_count() const noexcept;
    [[nodiscard]] std::size_t stored_tetrahedron_count() const noexcept;
    [[nodiscard]] std::size_t active_tetrahedron_count() const noexcept;

private:
    struct TetrahedronSlot {
        Tetrahedron tetrahedron{};
        bool active{true};
    };

    std::vector<Vertex> vertices_;
    std::vector<TetrahedronSlot> tetrahedra_;
};

} // namespace tetra

