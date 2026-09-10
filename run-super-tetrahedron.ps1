$cmake = "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
& $cmake --build build --config Release --target super_tetrahedron_demo

if ($LASTEXITCODE -eq 0) {
    .\build\Release\super_tetrahedron_demo.exe
}
