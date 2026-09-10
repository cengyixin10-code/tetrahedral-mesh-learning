# 网格生成模块

当前文件：SuperTetrahedron.hpp/.cpp。
职责：根据输入点的范围，创建一个包住全部输入点的初始四面体。

当前文件：FindBadTetrahedra.hpp/.cpp。
职责：使用 orient3d 和 inSphere，寻找插入新点时需要删除的旧四面体。

未来文件：DelaunayMesher.hpp/.cpp。
职责：从超级四面体开始，逐点插入并更新四面体连接关系。
基础点集版本完成后，再设计边界恢复与质量细化模块。
点集 Delaunay 不等同于任意实体内部的网格，复杂边界需要后续工作。
