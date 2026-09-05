@echo off
setlocal
cd /d "%~dp0"
echo This installs the pinned Pillow dependency into the Python interpreter you choose.
echo It does not install an A:M plugin or change an A:M project.
echo Press Ctrl+C to cancel, or continue.
pause
if not "%~1"=="" (
  "%~1" -m pip install -r requirements.txt
) else if defined PATCHDRAW_PYTHON (
  "%PATCHDRAW_PYTHON%" -m pip install -r requirements.txt
) else (
  py -3.12 -m pip install -r requirements.txt
)
set "RESULT=%ERRORLEVEL%"
echo.
if not "%RESULT%"=="0" echo Installation failed. Check the selected Python and the message above.
pause
exit /b %RESULT%
