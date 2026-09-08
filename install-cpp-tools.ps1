# 在你能处理 Windows 管理员授权窗口时运行此脚本。
# 使用微软 winget 官方目录，安装最小 C++ 编译组件，不自动重启。
$ErrorActionPreference = 'Stop'
winget install --id Microsoft.VisualStudio.2022.BuildTools --exact --source winget --accept-source-agreements --accept-package-agreements --override '--quiet --wait --norestart --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 --add Microsoft.VisualStudio.Component.Windows11SDK.26100 --add Microsoft.VisualStudio.Component.VC.CMake.Project' --disable-interactivity
if ($LASTEXITCODE -ne 0) { throw "Installer returned $LASTEXITCODE. Installation has not been verified." }
Write-Host 'Installer finished. Run build-and-test.ps1 to verify the compiler and TetGen.'
