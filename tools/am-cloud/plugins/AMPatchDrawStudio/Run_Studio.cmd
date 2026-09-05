@echo off
setlocal
cd /d "%~dp0"
if not "%~1"=="" (
  "%~1" -B runtime\patch_draw_studio.py
) else if defined PATCHDRAW_PYTHON (
  "%PATCHDRAW_PYTHON%" -B runtime\patch_draw_studio.py
) else (
  py -3.12 -B runtime\patch_draw_studio.py
)
if errorlevel 1 (
  echo.
  echo Studio did not start or reported an error. Read the message above.
  echo Use Run_Studio.cmd "C:\Path\To\python.exe" to choose Python explicitly.
  echo Tkinter and Pillow are required. Install_Dependencies.cmd is a separate, optional step.
  pause
  exit /b 1
)
