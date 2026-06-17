@echo off
chcp 65001 >nul

set /p projectName="Введите название нового Arduino Uno проекта: "
set "projectName=%projectName: =_%"
set "scriptDir=%~dp0"
set "templateDir=%scriptDir%Arduino Uno"
set "sketchesDir=%scriptDir%..\!Sketches\Arduino"
set "targetDir=%sketchesDir%\%projectName%"

if exist "%targetDir%" (
    echo.
    echo Ошибка: папка %projectName% уже существует!
    echo.
    pause
    exit /b
)

xcopy "%templateDir%" "%targetDir%\" /E /I /Q
ren "%targetDir%\Arduino Uno.ino" "%projectName%.ino"

code "%targetDir%"

echo.
echo Проект %projectName% создан и открыт в VS Code!
echo.
pause