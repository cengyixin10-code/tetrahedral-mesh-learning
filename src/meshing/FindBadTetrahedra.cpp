#include "meshing/FindBadTetrahedra.hpp"

#include "predicates/InSphere.hpp"
#include "predicates/Orientation.hpp"

namespace tetra {

std::vector<TetrahedronId> find_bad_tetrahedra(const Mesh& mesh, Vec3 point)
{
    std::vector<TetrahedronId> bad_tetrahedra;

    // 只检查当前仍然有效的四面体。
    for (TetrahedronId tetrahedron_id : mesh.active_tetrahedron_ids()) {
        const Tetrahedron& tetrahedron = mesh.tetrahedron(tetrahedron_id);

        // 四面体只保存顶点编号，所以要从 Mesh 中取得四个顶点的坐标。
        Vec3 a = mesh.vertex(tetrahedron.vertices[0]).position;
        Vec3 b = mesh.vertex(tetrahedron.vertices[1]).position;
        Vec3 c = mesh.vertex(tetrahedron.vertices[2]).position;
        Vec3 d = mesh.vertex(tetrahedron.vertices[3]).position;

        double orientation = orient3d(a, b, c, d);
        double sphere_result = inSphere(a, b, c, d, point);

        // 两个结果同号，说明新点位于这个四面体的外接球内部。
        // 使用乘积判断后，顶点顺序是正向还是反向都可以正确工作。
        if (orientation * sphere_result > 0.0) {
            bad_tetrahedra.push_back(tetrahedron_id);
        }
    }

    return bad_tetrahedra;
}

} // namespace tetra
