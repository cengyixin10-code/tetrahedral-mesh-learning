#pragma once

// Vec3.hpp 定义最基础的三维数学对象。
// 后续 Vertex 用它保存坐标，orient3d 和 inSphere 用它进行向量运算。

namespace tetra {

// Vec3 表示三个 double 数组成的三维量。
// 它既可以表示空间坐标，也可以表示两个点相减得到的方向向量。
struct Vec3 {
    // 后面的 {} 表示默认构造 Vec3 时把三个分量初始化为 0。
    double x{};
    double y{};
    double z{};

    // 向量加法：当前向量 + other，返回一个新向量。
    // 函数末尾的 const 表示不会修改当前向量本身。
    constexpr Vec3 operator+(const Vec3& other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    // 向量减法。两个点的坐标相减后，可以得到从一个点指向另一个点的向量。
    constexpr Vec3 operator-(const Vec3& other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    // 向量右乘一个标量，例如 vector * 2.0。
    constexpr Vec3 operator*(double scalar) const
    {
        return {x * scalar, y * scalar, z * scalar};
    }

    // 点积 a·b，结果是一个数。
    // 后续可用于距离、投影以及标量三重积的计算。
    constexpr double dot(const Vec3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    // 叉积 a×b，结果是一个垂直于 a、b 的新向量，方向遵循右手定则。
    constexpr Vec3 cross(const Vec3& other) const
    {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
        };
    }

    // 长度平方 |a|² = a·a。
    // 很多判断只需比较长度平方，因此可以避免较慢且不必要的开平方运算。
    constexpr double squared_norm() const
    {
        return dot(*this);
    }
};

// 这个独立函数补充“标量在左边”的写法，例如 2.0 * vector。
constexpr Vec3 operator*(double scalar, const Vec3& vector)
{
    return vector * scalar;
}

} // namespace tetra
