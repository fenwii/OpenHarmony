@echo off
set BASE_DIR=%~dp0
set PYTHON=python
set TOOLS=tools
cd /d %BASE_DIR%

(where %PYTHON% | findstr %PYTHON%) >nul 2>&1 || (
    @echo "Python3.7 or higher version required!"
    goto:eof
)

python -c "import sys; exit(1) if sys.version_info.major < 3 or sys.version_info.minor < 7 else exit(0)"
@if errorlevel 1 (
    @echo "Python3.7 or higher version required!"
    goto:eof
)

python -c "import easy_install"
@if errorlevel 1 (
    @echo "Please install setuptools first!"
    goto:eof
)

if not exist %TOOLS% (
    @echo "no %TOOLS% directory exist"
	goto:eof
)

for %%a in (%TOOLS%/*.egg) do (
    python -m easy_install --user %TOOLS%/%%a
    @if errorlevel 1 (
      @echo "Error occurs to install %%a!"
    )
)
python -m xdevice %*
