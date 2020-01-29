@echo off

SET CURRENT_PATH=%~dp0
SET BUILD_DIR="%CURRENT_PATH:~0,-1%\..\build"

PUSHD %BUILD_DIR%

cmake ../
cmake --build . --config Debug --target ila
.\Debug\ila.exe

POPD
PAUSE