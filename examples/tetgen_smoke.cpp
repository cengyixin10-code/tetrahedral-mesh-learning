// 仅用于确认第三方库可以链接、运行。暂时不要求学习这段代码。
// 它调用现成的 TetGen，不是我们自己实现的网格算法。
#include "tetgen.h"
#include <cmath>
#include <iostream>

int main()
{
    tetgenio input, output;
    input.firstnumber = 0;
    input.numberofpoints = 4;
    input.pointlist = new REAL[12]{0,0,0, 1,0,0, 0,1,0, 0,0,1};
    char options[] = "Q";
    try {
        tetrahedralize(options, &input, &output);
    } catch (int error) {
        std::cerr << "TetGen error: " << error << '\n';
        return 1;
    }
    if (output.numberofpoints != 4 || output.numberoftetrahedra != 1
        || output.numberofcorners != 4) return 2;
    bool seen[4]{};
    for (int i = 0; i < 4; ++i) {
        int index = output.tetrahedronlist[i] - output.firstnumber;
        if (index < 0 || index >= 4 || seen[index]) return 3;
        seen[index] = true;
    }
    std::cout << "TetGen OK: 4 points, 1 tetrahedron, valid connectivity.\n";
    return 0;
}
