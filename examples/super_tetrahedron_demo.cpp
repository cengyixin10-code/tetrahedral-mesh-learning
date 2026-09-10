#include "meshing/SuperTetrahedron.hpp"
#include "predicates/Orientation.hpp"

#include <iostream>
#include <vector>

int main()
{
    // 这些点是以后要进行四面体划分的输入点。
    std::vector<tetra::Vec3> points{
        {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.2, 0.2, 1.0},
        {0.5, 0.4, 0.3},
    };

    std::array<tetra::Vec3, 4> super = tetra::create_super_tetrahedron(points);

    for (int i = 0; i < 4; i++) {
        std::cout << "super[" << i << "] = ("
                  << super[i].x << ", "
                  << super[i].y << ", "
                  << super[i].z << ")\n";
    }

    double orientation = tetra::orient3d(super[0], super[1], super[2], super[3]);
    std::cout << "orient3d = " << orientation << '\n';

    return 0;
}
