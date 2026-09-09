#pragma once

// Mesh.hpp 声明网格的总容器及其对外操作。
// 这里只说明“能做什么”，函数的具体执行过程写在 Mesh.cpp 中。

#include "geometry/Tetrahedron.hpp"

#include <array>
#include <cstddef>
#include <vector>

namespace tetra {

// Mesh 统一拥有全部 Vertex 和 Tetrahedron 数据。
// 其他模块通过编号访问这里的数据，从而避免到处复制坐标和单元。
class Mesh {
public:
    // 加入一个新顶点。Mesh 自动分配编号，并把编号返回给调用者。
    VertexId add_vertex(Vec3 position);

    // 用四个已有 VertexId 创建四面体。返回新四面体的编号。
    TetrahedronId add_tetrahedron(std::array<VertexId, 4> vertices);

    // 根据编号只读访问顶点或四面体。
    // 返回引用可以避免复制对象；两个函数末尾的 const 保证它们不修改 Mesh。
    const Vertex& vertex(VertexId id) const;
    const Tetrahedron& tetrahedron(TetrahedronId id) const;

    // 判断四面体是否仍然有效。
    bool is_active(TetrahedronId id) const;

    // 把四面体标记为失效，但不从 vector 中真正擦除。
    // Bowyer-Watson 找到 Cavity 后会调用它“删除”旧单元。
    void deactivate_tetrahedron(TetrahedronId id);

    // 收集并返回当前所有有效四面体的编号。
    std::vector<TetrahedronId> active_tetrahedron_ids() const;

    // 三种数量查询。
    // stored 包含已经失效但仍留在数组中的四面体，active 只统计有效单元。
    // noexcept 表示这些简单查询保证不会抛出异常。
    std::size_t vertex_count() const noexcept;
    std::size_t stored_tetrahedron_count() const noexcept;
    std::size_t active_tetrahedron_count() const noexcept;

private:
    // Slot 把一个四面体和它的有效状态放在一起。
    // private 表示这个存储细节只允许 Mesh 自己使用。
    struct TetrahedronSlot {
        Tetrahedron tetrahedron{};
        bool active{true};
    };

    // vector 是可增长数组。新顶点和新四面体依次追加到末尾。
    std::vector<Vertex> vertices_;
    std::vector<TetrahedronSlot> tetrahedra_;
};

} // namespace tetra

