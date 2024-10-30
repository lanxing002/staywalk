@echo off
rem Used by the buildbot "remotedeploy" step.
setlocal

set PATH=%PATH%;%SystemRoot%\SysNative\OpenSSH;%SystemRoot%\System32\OpenSSH
set here=%~dp0

if %ERRORLEVEL% NEQ 0 (echo SSH does not work) & exit /b %ERRORLEVEL%

if "%PYTHON_SOURCE%"=="" (set PYTHON_SOURCE=%here%..\)
if "%REMOTE_PYTHON_DIR%"=="" (set REMOTE_PYTHON_DIR=%PYTHON_SOURCE%build)

if NOT "%REMOTE_PYTHON_DIR:~-1,1%"=="\" (set REMOTE_PYTHON_DIR=%REMOTE_PYTHON_DIR%\)
echo PYTHON_SOURCE = %PYTHON_SOURCE%
echo REMOTE_PYTHON_DIR = %REMOTE_PYTHON_DIR%

REM Create Python directories
mkdir %REMOTE_PYTHON_DIR%Modules
mkdir %REMOTE_PYTHON_DIR%PC

echo -----------------
echo %PYTHON_SOURCE%
echo %REMOTE_PYTHON_DIR%

@REM for /f "USEBACKQ" %%i in (`dir PCbuild\*.bat /b`) do copy PCBuild\%%i "%REMOTE_PYTHON_DIR%PCBuild"
for /f "USEBACKQ" %%i in (`dir %PYTHON_SOURCE%PCbuild\*.bat /b`) do cp %PYTHON_SOURCE%PCbuild\%%i "%REMOTE_PYTHON_DIR%PCBuild"
for /f "USEBACKQ" %%i in (`dir %PYTHON_SOURCE%PCbuild\*.py /b`) do @scp %PYTHON_SOURCE%PCbuild\%%i "%REMOTE_PYTHON_DIR%PCBuild"

scp -r "%PYTHON_SOURCE%Include" "%REMOTE_PYTHON_DIR%Include"
scp -r "%PYTHON_SOURCE%Lib" "%REMOTE_PYTHON_DIR%Lib"
scp -r "%PYTHON_SOURCE%Parser" "%REMOTE_PYTHON_DIR%Parser"
scp -r "%PYTHON_SOURCE%Tools" "%REMOTE_PYTHON_DIR%Tools"
scp "%PYTHON_SOURCE%Modules\Setup" "%REMOTE_PYTHON_DIR%Modules"
scp "%PYTHON_SOURCE%PC\pyconfig.h" "%REMOTE_PYTHON_DIR%PC"

echo -------------------

exit /b %ERRORLEVEL%
