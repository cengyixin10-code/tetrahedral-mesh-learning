# 自动找到已安装的 CMake，再配置、编译和验证项目。
$ErrorActionPreference = 'Stop'
$cmakeCommand = Get-Command cmake -ErrorAction SilentlyContinue
if ($cmakeCommand) {
    $cmakeExe = $cmakeCommand.Source
} else {
    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path $vswhere)) { throw 'Visual Studio Build Tools is not installed yet.' }
    $vsPath = & $vswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.CMake.Project -property installationPath
    $cmakeExe = Join-Path $vsPath 'Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe'
}
if (-not (Test-Path $cmakeExe)) { throw 'CMake was not found.' }
$ctestExe = Join-Path (Split-Path $cmakeExe) 'ctest.exe'
Push-Location $PSScriptRoot
try {
    & $cmakeExe --preset windows-msvc
    if ($LASTEXITCODE -ne 0) { throw 'CMake configuration failed.' }
    & $cmakeExe --build --preset release --parallel 2
    if ($LASTEXITCODE -ne 0) { throw 'Compilation failed.' }
    & $ctestExe --preset release
    if ($LASTEXITCODE -ne 0) { throw 'Verification failed.' }
} finally { Pop-Location }
