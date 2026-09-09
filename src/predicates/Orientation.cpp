#include "predicates/Orientation.hpp"

namespace tetra {

double orient3d(Vec3 a, Vec3 b, Vec3 c, Vec3 d)
{
    // 以 a 为共同起点，构造三条边。
    Vec3 ab = b - a;
    Vec3 ac = c - a;
    Vec3 ad = d - a;

    // ab×ac 得到平面 abc 的法向量。
    // 再与 ad 做点积，结果的正负表示 d 位于平面的哪一侧。
    return ab.cross(ac).dot(ad);
}

} // namespace tetra
