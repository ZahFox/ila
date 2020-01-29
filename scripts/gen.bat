@echo off

SET CURRENT_PATH=%~dp0
SET BUILD_DIR="%CURRENT_PATH:~0,-1%\..\build"
SET VENDOR_DIR="%CURRENT_PATH:~0,-1%\..\vendor"

RMDIR /S /Q %BUILD_DIR%
MKDIR %BUILD_DIR%
PUSHD %BUILD_DIR%

cmake ../
MKDIR Debug
MKDIR Release
COPY %VENDOR_DIR%\_bin\ Debug
COPY %VENDOR_DIR%\_bin\ Release

POPD
PAUSE