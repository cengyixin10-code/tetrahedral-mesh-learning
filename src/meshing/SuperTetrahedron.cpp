#include "meshing/SuperTetrahedron.hpp"

#include <algorithm>

namespace tetra {

std::array<Vec3, 4> create_super_tetrahedron(std::vector<Vec3> points)
{
    // 没有输入点时，返回一个以原点为中心的默认四面体。
    if (points.empty()) {
        return {{{1.0, 1.0, 1.0},
                 {-1.0, -1.0, 1.0},
                 {-1.0, 1.0, -1.0},
                 {1.0, -1.0, -1.0}}};
    }

    // 从第一个点开始，寻找所有点在 x、y、z 三个方向上的最小值和最大值。
    Vec3 minimum = points[0];
    Vec3 maximum = points[0];

    for (Vec3 point : points) {
        minimum.x = std::min(minimum.x, point.x);
        minimum.y = std::min(minimum.y, point.y);
        minimum.z = std::min(minimum.z, point.z);

        maximum.x = std::max(maximum.x, point.x);
        maximum.y = std::max(maximum.y, point.y);
        maximum.z = std::max(maximum.z, point.z);
    }

    // 包围盒中心就是超级四面体的中心。
    Vec3 center{
        (minimum.x + maximum.x) / 2.0,
        (minimum.y + maximum.y) / 2.0,
        (minimum.z + maximum.z) / 2.0,
    };

    // 找出包围盒最长的一条边，再把四面体放大四倍。
    double width = maximum.x - minimum.x;
    double height = maximum.y - minimum.y;
    double depth = maximum.z - minimum.z;
    double size = std::max({width, height, depth});

    // 所有输入点重合时，size 会是 0，所以给它一个默认大小。
    if (size == 0.0) {
        size = 1.0;
    }

    double scale = size * 4.0;

    // 这四个顶点围绕 center 对称，并按正方向排列。
    return {{{center.x + scale, center.y + scale, center.z + scale},
             {center.x - scale, center.y - scale, center.z + scale},
             {center.x - scale, center.y + scale, center.z - scale},
             {center.x + scale, center.y - scale, center.z - scale}}};
}

} // namespace tetra
