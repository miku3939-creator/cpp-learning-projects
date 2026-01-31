@echo off
echo ========================================
echo   生命游戏项目自动编译脚本
echo ========================================

echo 步骤1: 检查必要文件...
if not exist "src\LifeGameWithUI.cpp" (
    echo 错误: 找不到 src\LifeGameWithUI.cpp
    pause
    exit /b 1
)

if not exist "src\UIComponents.cpp" (
    echo 错误: 找不到 src\UIComponents.cpp
    pause
    exit /b 1
)

echo 步骤2: 创建输出目录...
if not exist "bin" mkdir bin

echo 步骤3: 开始编译...
g++ src\LifeGameWithUI.cpp src\UIComponents.cpp -o bin\LifeGame.exe -I src -lgdi32 -luuid -lEasyXa -mwindows -std=c++11

echo 步骤4: 检查编译结果...
if %errorlevel% == 0 (
    echo.
    echo ? 编译成功！
    echo ?? 可执行文件位置: bin\LifeGame.exe
    echo.
    echo 运行方法:
    echo   1. 双击 bin\LifeGame.exe
    echo   2. 或在命令行输入: bin\LifeGame.exe
) else (
    echo.
    echo ? 编译失败！
    echo.
    echo 可能的原因:
    echo   - 未安装C++编译器 (g++)
    echo   - 未安装EasyX图形库
    echo   - 库文件路径配置错误
    echo.
    echo 解决方案:
    echo   1. 安装 MinGW-w64 或 Visual Studio
    echo   2. 从 https://easyx.cn 下载安装EasyX
    echo   3. 确保库文件路径正确

)

echo.
pause