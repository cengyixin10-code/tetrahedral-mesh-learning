#include "geometry/Vec3.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace {

void expect_near(double actual, double expected, const char* label)
{
    constexpr double tolerance = 1e-12;
    if (std::abs(actual - expected) > tolerance) {
        std::cerr << label << ": expected " << expected << ", got " << actual << '\n';
        std::exit(1);
    }
}

void expect_vec_near(const tetra::Vec3& actual, const tetra::Vec3& expected, const char* label)
{
    expect_near(actual.x, expected.x, label);
    expect_near(actual.y, expected.y, label);
    expect_near(actual.z, expected.z, label);
}

} // namespace

int main()
{
    using tetra::Vec3;

    const Vec3 a{1.0, 2.0, 3.0};
    const Vec3 b{-2.0, 0.5, 4.0};

    expect_vec_near(a + b, {-1.0, 2.5, 7.0}, "vector addition");
    expect_vec_near(a - b, {3.0, 1.5, -1.0}, "vector subtraction");
    expect_vec_near(2.0 * a, {2.0, 4.0, 6.0}, "left scalar multiplication");
    expect_vec_near(b * 2.0, {-4.0, 1.0, 8.0}, "right scalar multiplication");
    expect_near(a.dot(b), 11.0, "dot product");
    expect_near(a.squared_norm(), 14.0, "squared norm");
    expect_vec_near(a.cross(b), {6.5, -10.0, 4.5}, "cross product");

    // x×y=z，且 (x×y)·z=1：确认叉积方向和标量三重积。
    const Vec3 x_axis{1.0, 0.0, 0.0};
    const Vec3 y_axis{0.0, 1.0, 0.0};
    const Vec3 z_axis{0.0, 0.0, 1.0};
    const Vec3 normal = x_axis.cross(y_axis);
    expect_vec_near(normal, z_axis, "right-hand-rule direction");
    expect_near(normal.dot(z_axis), 1.0, "scalar triple product");

    std::cout << "Vec3 tests passed\n";
    return 0;
}
