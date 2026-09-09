#include "predicates/Orientation.hpp"

#include <iostream>

int main()
{
    tetra::Vec3 a{0.0, 0.0, 0.0};
    tetra::Vec3 b{1.0, 0.0, 0.0};
    tetra::Vec3 c{0.0, 1.0, 0.0};
    tetra::Vec3 d{0.0, 0.0, 1.0};

    double result = tetra::orient3d(a, b, c, d);
    double volume = result / 6.0;

    std::cout << "orient3d = " << result << '\n';
    std::cout << "volume = " << volume << '\n';

    return 0;
}
