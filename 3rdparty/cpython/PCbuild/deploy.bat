@echo off
rem Used by the buildbot "remotedeploy" step.
setlocal

set PATH=%PATH%;%SystemRoot%\SysNative\OpenSSH;%SystemRoot%\System32\OpenSSH
set here=%~dp0

if %ERRORLEVEL% NEQ 0 (echo SSH does not work) & exit /b %ERRORLEVEL%

if "%PYTHON_SOURCE%"=="" (set PYTHON_SOURCE=%here%..\)
if "%REMOTE_PYTHON_DIR%"=="" (set REMOTE_PYTHON_DIR=%PYTHON_SOURCE%build)

mkdir %REMOTE_PYTHON_DIR%

if NOT "%REMOTE_PYTHON_DIR:~-1,1%"=="\" (set REMOTE_PYTHON_DIR=%REMOTE_PYTHON_DIR%\)
echo PYTHON_SOURCE = %PYTHON_SOURCE%
echo REMOTE_PYTHON_DIR = %REMOTE_PYTHON_DIR%

REM Create Python directories
echo -----------------
echo %PYTHON_SOURCE%
echo %REMOTE_PYTHON_DIR%


@REM for /f "USEBACKQ" %%i in (`dir PCbuild\*.bat /b`) do copy PCBuild\%%i "%REMOTE_PYTHON_DIR%PCBuild"
@REM for /f "USEBACKQ" %%i in (`dir %PYTHON_SOURCE%PCbuild\*.bat /b`) do cp %PYTHON_SOURCE%PCbuild\%%i "%REMOTE_PYTHON_DIR%PCBuild"
@REM for /f "USEBACKQ" %%i in (`dir %PYTHON_SOURCE%PCbuild\*.py /b`) do cp %PYTHON_SOURCE%PCbuild\%%i "%REMOTE_PYTHON_DIR%PCBuild"

cp -r "%PYTHON_SOURCE%Include" "%REMOTE_PYTHON_DIR%Include" > nul
cp -r "%PYTHON_SOURCE%Lib" "%REMOTE_PYTHON_DIR%Lib" > nul
cp -r "%PYTHON_SOURCE%Tools" "%REMOTE_PYTHON_DIR%Tools" > nul
cp "%PYTHON_SOURCE%PC\pyconfig.h" "%REMOTE_PYTHON_DIR%Include"

echo -------------------

exit /b %ERRORLEVEL%
