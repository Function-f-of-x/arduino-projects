@echo off
chcp 65001 >nul

set /p projectName="Введите название нового STM32 проекта: "
set "projectName=%projectName: =_%"
set "scriptDir=%~dp0"
set "templateDir=%scriptDir%STM32"
set "sketchesDir=%scriptDir%..\!Sketches\STM32"
set "targetDir=%sketchesDir%\%projectName%"

if exist "%targetDir%" (
    echo.
    echo Ошибка: папка %projectName% уже существует!
    echo.
    pause
    exit /b
)

xcopy "%templateDir%" "%targetDir%\" /E /I /Q
ren "%targetDir%\STM32.ino" "%projectName%.ino"

code "%targetDir%"

echo.
echo Проект %projectName% создан и открыт в VS Code!
echo.
pause