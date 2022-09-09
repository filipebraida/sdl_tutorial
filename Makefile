init:
	gcc -o game src/01_init.c -lSDL2main -lSDL2

window:
	gcc -o game src/02_window.c -lSDL2main -lSDL2

background:
	gcc -o game src/03_background.c -lSDL2main -lSDL2 -lSDL2_image

image:
	gcc -o game src/04_image.c -lSDL2main -lSDL2 -lSDL2_image

keyboard:
	gcc -o game src/05_keyboard.c -lSDL2main -lSDL2 -lSDL2_image

running:
	gcc -o game src/06_running.c -lSDL2main -lSDL2 -lSDL2_image

plotting:
	gcc -o game src/07_plotting.c -lSDL2main -lSDL2 -lSDL2_image

run:
	./game

install:
	sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev