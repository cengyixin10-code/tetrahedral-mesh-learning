#include "predicates/InSphere.hpp"

namespace tetra {

// 计算一个 3×3 行列式。
double determinant3(
    double a, double b, double c,
    double d, double e, double f,
    double g, double h, double i)
{
    return a * (e * i - f * h)
         - b * (d * i - f * g)
         + c * (d * h - e * g);
}

double inSphere(Vec3 a, Vec3 b, Vec3 c, Vec3 d, Vec3 e)
{
    // 把待判断点 e 移动到坐标原点，计算会简单很多。
    Vec3 ae = a - e;
    Vec3 be = b - e;
    Vec3 ce = c - e;
    Vec3 de = d - e;

    // 每个点到 e 的距离平方。
    double a2 = ae.squared_norm();
    double b2 = be.squared_norm();
    double c2 = ce.squared_norm();
    double d2 = de.squared_norm();

    // 这是 inSphere 的 4×4 行列式，按第一行展开计算。
    double determinant =
          ae.x * determinant3(be.y, be.z, b2, ce.y, ce.z, c2, de.y, de.z, d2)
        - ae.y * determinant3(be.x, be.z, b2, ce.x, ce.z, c2, de.x, de.z, d2)
        + ae.z * determinant3(be.x, be.y, b2, ce.x, ce.y, c2, de.x, de.y, d2)
        - a2   * determinant3(be.x, be.y, be.z, ce.x, ce.y, ce.z, de.x, de.y, de.z);

    // 调整符号，使正方向四面体的“球内”结果为正数。
    return -determinant;
}

} // namespace tetra
