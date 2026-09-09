#include "predicates/InSphere.hpp"
#include "predicates/Orientation.hpp"

#include <iostream>

int main()
{
    tetra::Vec3 a{0.0, 0.0, 0.0};
    tetra::Vec3 b{1.0, 0.0, 0.0};
    tetra::Vec3 c{0.0, 1.0, 0.0};
    tetra::Vec3 d{0.0, 0.0, 1.0};

    // 改变 e 的坐标，可以观察球内、球面和球外三种结果。
    tetra::Vec3 e{0.5, 0.5, 0.5};

    double orientation = tetra::orient3d(a, b, c, d);
    double result = tetra::inSphere(a, b, c, d, e);

    std::cout << "orient3d = " << orientation << '\n';
    std::cout << "inSphere = " << result << '\n';

    return 0;
}
