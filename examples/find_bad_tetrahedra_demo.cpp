#include "geometry/Mesh.hpp"
#include "meshing/FindBadTetrahedra.hpp"

#include <iostream>
#include <vector>

int main()
{
    tetra::Mesh mesh;

    // 第一个四面体位于原点附近。
    tetra::VertexId a = mesh.add_vertex({0.0, 0.0, 0.0});
    tetra::VertexId b = mesh.add_vertex({1.0, 0.0, 0.0});
    tetra::VertexId c = mesh.add_vertex({0.0, 1.0, 0.0});
    tetra::VertexId d = mesh.add_vertex({0.0, 0.0, 1.0});
    mesh.add_tetrahedron({a, b, c, d});

    // 第二个四面体放在较远的位置。
    tetra::VertexId e = mesh.add_vertex({5.0, 5.0, 5.0});
    tetra::VertexId f = mesh.add_vertex({6.0, 5.0, 5.0});
    tetra::VertexId g = mesh.add_vertex({5.0, 6.0, 5.0});
    tetra::VertexId h = mesh.add_vertex({5.0, 5.0, 6.0});
    mesh.add_tetrahedron({e, f, g, h});

    // 这个新点位于第一个四面体的外接球内部。
    tetra::Vec3 new_point{0.2, 0.2, 0.2};

    std::vector<tetra::TetrahedronId> bad =
        tetra::find_bad_tetrahedra(mesh, new_point);

    std::cout << "bad tetrahedron count = " << bad.size() << '\n';
    for (tetra::TetrahedronId id : bad) {
        std::cout << "bad tetrahedron id = " << id << '\n';
    }

    return 0;
}
