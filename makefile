SDLFLAGS = -I /usr/local/Cellar/sdl2/2.0.7/include -L /usr/local/Cellar/sdl2/2.0.7/lib -l SDL2-2.0.0
OPENGLFLAGS = -framework Opengl
CC = g++
MAIN = main.cpp
EXEC = main


all: #triMesh.o offLoader.o
	$(CC) $(MAIN) -o $(EXEC) $(SDLFLAGS) $(OPENGLFLAGS)

#triMesh.o:
#	$(CC) include/triMesh.cpp -c

#offLoader.o:
#	$(CC) include/offLoader.cpp -c

run: 
	clear
	./main

clean:
	rm *.o