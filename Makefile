window:
	gcc -o game src/01_window.c -lSDL2main -lSDL2

keyboard:
	gcc -o game src/02_keyboard.c -lSDL2main -lSDL2

background:
	gcc -o game src/03_background.c -lSDL2main -lSDL2 -lSDL2_image

ex4:
	gcc -o game sdl4.c -lSDL2main -lSDL2 -lSDL2_image

run:
	./game

install:
	sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev