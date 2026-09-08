#pragma once

namespace tetra {

// 一个三维向量，也可暂时用于存储一个点的 (x, y, z) 坐标。
struct Vec3 {
    double x{};
    double y{};
    double z{};

    [[nodiscard]] constexpr Vec3 operator+(const Vec3& other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    [[nodiscard]] constexpr Vec3 operator-(const Vec3& other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    [[nodiscard]] constexpr Vec3 operator*(double scalar) const
    {
        return {x * scalar, y * scalar, z * scalar};
    }

    // 点积：a·b。后续可用于距离、投影和行列式计算。
    [[nodiscard]] constexpr double dot(const Vec3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    // 叉积：a×b。结果方向由右手定则决定。
    [[nodiscard]] constexpr Vec3 cross(const Vec3& other) const
    {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
        };
    }

    // 不开平方的长度 |a|²，避免后续几何判断中不必要的 sqrt。
    [[nodiscard]] constexpr double squared_norm() const
    {
        return dot(*this);
    }
};

[[nodiscard]] constexpr Vec3 operator*(double scalar, const Vec3& vector)
{
    return vector * scalar;
}

} // namespace tetra
