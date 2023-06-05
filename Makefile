image: main.o
	gcc main.o -L ./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o image.exe 
mixer: main.o
	gcc main.o -L ./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o mixer.exe
main.o: main.c
	gcc -I ./include main.c -c