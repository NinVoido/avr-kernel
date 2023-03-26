all: main
asm:
	avr-gcc -mmcu=atmega328p main.c -S
upload: main
	avrdude -c arduino -p m328p -P /dev/arduino-uno -b 115200 -U flash:w:main
qemu: debug
	qemu-system-avr -machine uno -bios main_debug -s -S
main: main.c os/kernel.c os/config.c os/config.h os/kernel.h os/task_context.h
	avr-gcc -mmcu=atmega328p main.c os/kernel.c os/config.c -o main
debug: main.c os/kernel.c os/config.c os/config.h os/kernel.h os/task_context.h
	avr-gcc -mmcu=atmega328p main.c os/kernel.c os/config.c -o main_debug -g
clean:
	#rm *.o
	rm main;
	rm main_debug
