## Подготовка Windows к работе с Arduino.
### Установка программ
- AVRA - [ZIP-архив](https://sourceforge.net/projects/avra/files/1.2.3/avra-1.2.3-win32.zip/download) с AVRA, готовый exe-файл будет в папке bin.
- avr-gcc - [установщик](https://sourceforge.net/projects/winavr/files/latest/download). Запустите, отметьте все галочки.
- AVRDUDE - [ZIP-архив](https://github.com/mariusgreuel/avrdude/releases). Скачивайте подходящий релиз, exe-файл будет в распакованной папке.
### Компиляция
AVRA и avr-gcc работают так же, как и на Linux.
### Загрузка
Необходимо узнать COM-порт, к которому подключено Arduino. Откройте Менеджер Устройств, откройте вкладку Порты (COM и LPT), выберите единственный порт. В конце названия в скобках будет указан порт. Для примера возьмем COM3.\
Дальше avrdude работает так же, как и на Linux, просто в параметре порта (-P) указывайте порт, найденный в Менеджере Устройств. Пример - `avrdude.exe -c arduino -P COM3 -p m328p -U flash:w:avr-kernel/src/C/main`
