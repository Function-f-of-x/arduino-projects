@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo ========================================
echo   Конвертация проектов Arduino Uno
echo   в английские названия
echo ========================================
echo.

set "scriptDir=%~dp0"
set "sketchesDir=%scriptDir%..\!Sketches\Arduino"
set "templateVSCode=%scriptDir%Arduino Uno\.vscode"

:: Счётчики
set "totalCount=0"
set "successCount=0"
set "errorCount=0"

:: Проходим по всем папкам в !Sketches\Arduino
for /d %%D in ("%sketchesDir%\*") do (
    set "oldName=%%~nxD"
    set "newName="
    
    :: Перевод названий
    call :TranslateName "!oldName!" newName
    
    if defined newName (
        set /a totalCount+=1
        set "oldPath=%%D"
        set "newPath=%sketchesDir%\!newName!"
        
        echo [!totalCount!] Обработка: "!oldName!"
        echo      --^> "!newName!"
        
        :: Проверяем, не существует ли уже папка с таким именем
        if exist "!newPath!" (
            echo      ОШИБКА: Папка "!newName!" уже существует!
            echo.
            set /a errorCount+=1
        ) else (
            :: Переименовываем папку
            ren "!oldPath!" "!newName!"
            
            :: Ищем и переименовываем .ino файл
            for /f "delims=" %%F in ('dir "!newPath!\*.ino" /b') do (
                set "oldIno=%%F"
                set "newIno=!newName!.ino"
                
                if not "!oldIno!"=="!newIno!" (
                    ren "!newPath!\!oldIno!" "!newIno!"
                    echo      .ino переименован: "!oldIno!" --^> "!newIno!"
                )
            )
            
            :: Удаляем build если есть
            if exist "!newPath!\build\" (
                rd /s /q "!newPath!\build"
                echo      Удалена папка build
            )
            
            :: Удаляем .vscode если есть
            if exist "!newPath!\.vscode\" (
                rd /s /q "!newPath!\.vscode"
                echo      Удалена папка .vscode
            )
            
            :: Копируем .vscode из шаблона
            if exist "%templateVSCode%" (
                xcopy "%templateVSCode%" "!newPath!\.vscode\" /E /I /Q >nul
                echo      Скопирован .vscode из шаблона
            )
            
            set /a successCount+=1
            echo      УСПЕШНО!
            echo.
        )
    )
)

echo ========================================
echo   Завершено!
echo   Всего обработано: %totalCount%
echo   Успешно: %successCount%
echo   Ошибок: %errorCount%
echo ========================================
echo.
pause
exit /b

:: ========================================
::   Функция перевода названий
:: ========================================
:TranslateName
set "input=%~1"
set "outputVar=%~2"

:: Приводим к нижнему регистру для сравнения
set "inputLower=%input%"

:: Переводы (русский --^> английский с подчёркиваниями)
if "!inputLower!"=="[Сигнализация по вай-фаю]" set "newName=WiFi_Alarm"
if "!inputLower!"=="[Температура-влажность без деталей]" set "newName=Temp_Humidity_Simple"
if "!inputLower!"=="[Температура-влажность на смартме без кнопки]" set "newName=Temp_Humidity_Smartme_NoButton"
if "!inputLower!"=="[Температура-влажность на смартме без кнопки на фоне]" set "newName=Temp_Humidity_Smartme_NoButton_BG"
if "!inputLower!"=="[Температура-влажность на смартме с кнопкой]" set "newName=Temp_Humidity_Smartme_WithButton"
if "!inputLower!"=="[Температура-влажность на смартме с кнопкой на фоне]" set "newName=Temp_Humidity_Smartme_WithButton_BG"
if "!inputLower!"=="[Температура-давление на Serial]" set "newName=Temp_Pressure_Serial"
if "!inputLower!"=="[Часы реального времени]" set "newName=RTC_Clock"
if "!inputLower!"=="[Часы реального времени lcd]" set "newName=RTC_Clock_LCD"
if "!inputLower!"=="[Часы реального времени wi-fi]" set "newName=RTC_Clock_WiFi"
if "!inputLower!"=="[Бегущие огоньки]" set "newName=Running_Lights"
if "!inputLower!"=="[Бегущие туда-сюда огоньки]" set "newName=Running_Lights_BackForth"
if "!inputLower!"=="[Бесконтактный выключатель]" set "newName=Touchless_Switch"
if "!inputLower!"=="[Вай-фай кнопки-выключатели]" set "newName=WiFi_Switch_Buttons"
if "!inputLower!"=="[Время Serial]" set "newName=Time_Serial"
if "!inputLower!"=="[Время со включения света]" set "newName=Time_Since_Light_On"
if "!inputLower!"=="[Датчик препятствия вай-фай]" set "newName=Obstacle_Sensor_WiFi"
if "!inputLower!"=="[День недели]" set "newName=Day_Of_Week"
if "!inputLower!"=="[Длинная светяшка]" set "newName=Long_LED_Strip"
if "!inputLower!"=="[Журнал отключений]" set "newName=Power_Off_Log"
if "!inputLower!"=="[Змейка]" set "newName=Snake_Game"
if "!inputLower!"=="[Инфракрасный датчик препятствия]" set "newName=IR_Obstacle_Sensor"
if "!inputLower!"=="[Клававиатура]" set "newName=Keypad"
if "!inputLower!"=="[Мелодии на расстоянии]" set "newName=Melodies_On_Distance"
if "!inputLower!"=="[Меню]" set "newName=Menu"
if "!inputLower!"=="[Меню OLED]" set "newName=Menu_OLED"
if "!inputLower!"=="[Метеостанция по wi-fi (Текст сверху показания снизу) без кнопки]" set "newName=Weather_Station_WiFi_TextTop_NoButton"
if "!inputLower!"=="[Метеостанция по wi-fi (Текст сверху показания снизу) с кнопкой]" set "newName=Weather_Station_WiFi_TextTop_WithButton"
if "!inputLower!"=="[Метеостанция по wi-fi (Текст слева показания справа) без кнопки]" set "newName=Weather_Station_WiFi_TextLeft_NoButton"
if "!inputLower!"=="[Метеостанция по wi-fi (Текст слева показания справа) с кнопкой]" set "newName=Weather_Station_WiFi_TextLeft_WithButton"
if "!inputLower!"=="[Метеостанция + дата-время wi-fi]" set "newName=Weather_Station_DateTime_WiFi"
if "!inputLower!"=="[Напряжение по usb]" set "newName=USB_Voltage"
if "!inputLower!"=="[Определение кодов кнопок пульта]" set "newName=IR_Button_Codes_Detector"
if "!inputLower!"=="[Остановка]" set "newName=Stop"
if "!inputLower!"=="[Песня С днём рождения]" set "newName=Happy_Birthday_Song"
if "!inputLower!"=="[Поздравление с восьмым марта]" set "newName=March_8_Congrats"
if "!inputLower!"=="[Проверка аккумуляторов]" set "newName=Battery_Checker"
if "!inputLower!"=="[Проверка сигнала с кнопки]" set "newName=Button_Signal_Check"
if "!inputLower!"=="[Проверка шрифта]" set "newName=Font_Check"
if "!inputLower!"=="[Реле мигание]" set "newName=Relay_Blink"
if "!inputLower!"=="[Реле управление с вай-фая]" set "newName=Relay_WiFi_Control"
if "!inputLower!"=="[Секундомер]" set "newName=Stopwatch"
if "!inputLower!"=="[Сигнализация]" set "newName=Alarm"

:: Если перевод найден, возвращаем его
if defined newName (
    set "%outputVar%=!newName!"
) else (
    echo      ПРЕДУПРЕЖДЕНИЕ: Не найден перевод для "!input!"
    echo      Пропускаем...
    echo.
    set "%outputVar%="
)

exit /b