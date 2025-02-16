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

xcopy "%PYTHON_SOURCE%Include" "%REMOTE_PYTHON_DIR%Include" /E /H /C /I
xcopy "%PYTHON_SOURCE%Lib" "%REMOTE_PYTHON_DIR%Lib" /E /H /C /I
xcopy "%PYTHON_SOURCE%Tools" "%REMOTE_PYTHON_DIR%Tools" /E /H /C /I
cp "%PYTHON_SOURCE%PC\pyconfig.h" "%REMOTE_PYTHON_DIR%Include"

echo -------------------

exit /b %ERRORLEVEL%
