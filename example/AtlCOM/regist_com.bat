@echo off
setlocal
echo  "%~1"
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo Need admin privilege
    exit /b 1
)

if "%~1"=="" (
    echo usage：register_com.bat "Path\To\MyCom.dll"
    pause
    exit /b 1
)

if not exist "%~1" (
    echo Non exist: %~1
    pause
    exit /b 1
)

regsvr32 /s /u "%~1"

regsvr32 /s "%~1"

pause
endlocal