#include "geometry/Mesh.hpp"

#include <algorithm>
#include <stdexcept>

namespace tetra {

VertexId Mesh::add_vertex(Vec3 position)
{
    const VertexId id = vertices_.size();
    vertices_.push_back({id, position});
    return id;
}

TetrahedronId Mesh::add_tetrahedron(std::array<VertexId, 4> vertices)
{
    for (const VertexId id : vertices) {
        if (id >= vertices_.size()) {
            throw std::out_of_range("A tetrahedron references a vertex that is not in this mesh.");
        }
    }

    auto sorted_vertices = vertices;
    std::sort(sorted_vertices.begin(), sorted_vertices.end());
    if (std::adjacent_find(sorted_vertices.begin(), sorted_vertices.end()) != sorted_vertices.end()) {
        throw std::invalid_argument("The four vertices of a tetrahedron must be distinct.");
    }

    const TetrahedronId id = tetrahedra_.size();
    tetrahedra_.push_back({{vertices}, true});
    return id;
}

const Vertex& Mesh::vertex(VertexId id) const
{
    return vertices_.at(id);
}

const Tetrahedron& Mesh::tetrahedron(TetrahedronId id) const
{
    return tetrahedra_.at(id).tetrahedron;
}

bool Mesh::is_active(TetrahedronId id) const
{
    return tetrahedra_.at(id).active;
}

void Mesh::deactivate_tetrahedron(TetrahedronId id)
{
    tetrahedra_.at(id).active = false;
}

std::vector<TetrahedronId> Mesh::active_tetrahedron_ids() const
{
    std::vector<TetrahedronId> ids;
    ids.reserve(tetrahedra_.size());
    for (TetrahedronId id = 0; id < tetrahedra_.size(); ++id) {
        if (tetrahedra_[id].active) {
            ids.push_back(id);
        }
    }
    return ids;
}

std::size_t Mesh::vertex_count() const noexcept
{
    return vertices_.size();
}

std::size_t Mesh::stored_tetrahedron_count() const noexcept
{
    return tetrahedra_.size();
}

std::size_t Mesh::active_tetrahedron_count() const noexcept
{
    return static_cast<std::size_t>(std::count_if(
        tetrahedra_.begin(), tetrahedra_.end(),
        [](const TetrahedronSlot& slot) { return slot.active; }));
}

} // namespace tetra

