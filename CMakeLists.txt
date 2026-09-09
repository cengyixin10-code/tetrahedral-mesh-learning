# 构建说明书：告诉 CMake 用哪些文件生成哪些程序。
cmake_minimum_required(VERSION 3.20)
project(TetraLearning LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
  add_compile_options(/utf-8)
endif()

# 学习程序：目前只输出一句话。
add_executable(hello_world examples/hello_world.cpp)

# 教学算法代码：基础数据结构和 orient3d。
add_library(tetra_core
  src/geometry/Mesh.cpp
  src/predicates/Orientation.cpp
)
target_include_directories(tetra_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
add_executable(test_vec3 tests/test_vec3.cpp)
target_link_libraries(test_vec3 PRIVATE tetra_core)

# V0.1-5 的直观演示：给定四个点，打印 orient3d 的计算结果。
add_executable(orient3d_demo examples/orient3d_demo.cpp)
target_link_libraries(orient3d_demo PRIVATE tetra_core)

# TetGen 是本地参考材料，不随本教学仓库上传。存在时才构建其演示目标。
set(TETGEN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/reference/tetgen")
if(EXISTS "${TETGEN_DIR}/tetgen.cxx")
  # 使用独立构建规则适配现代 CMake，不改动 TetGen 原始源码。
  add_library(tetgen_reference STATIC
    "${TETGEN_DIR}/tetgen.cxx" "${TETGEN_DIR}/predicates.cxx")
  target_include_directories(tetgen_reference PUBLIC "${TETGEN_DIR}")
  target_compile_definitions(tetgen_reference PUBLIC TETLIBRARY)
  add_executable(tetgen_cli
    "${TETGEN_DIR}/tetgen.cxx" "${TETGEN_DIR}/predicates.cxx")
  # 几何判断依赖严格的浮点运算，不使用快速浮点优化。
  if(MSVC)
    set_source_files_properties("${TETGEN_DIR}/predicates.cxx"
      PROPERTIES COMPILE_OPTIONS "/Od;/fp:strict")
  else()
    set_source_files_properties("${TETGEN_DIR}/predicates.cxx"
      PROPERTIES COMPILE_OPTIONS "-O0;-fno-fast-math;-ffp-contract=off")
  endif()
  add_executable(tetgen_smoke examples/tetgen_smoke.cpp)
  target_link_libraries(tetgen_smoke PRIVATE tetgen_reference)
else()
  message(STATUS "TetGen source is absent: only learning targets will be built.")
endif()
enable_testing()
add_test(NAME hello_world COMMAND hello_world)
set_tests_properties(hello_world PROPERTIES PASS_REGULAR_EXPRESSION "Hello, tetrahedral mesh!")
add_test(NAME vec3 COMMAND test_vec3)
set_tests_properties(vec3 PROPERTIES PASS_REGULAR_EXPRESSION "Vec3 tests passed")
if(TARGET tetgen_smoke)
  add_test(NAME tetgen_library_smoke COMMAND tetgen_smoke)
endif()

