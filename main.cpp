#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl.h>
#include "include/offLoader.h"
#include "include/triMesh.h"
#include "include/photon.h"

using namespace std;

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500  

//The window we'll be rendering to 
SDL_Window* window = NULL; 
SDL_GLContext wContext;

void SDLINIT();
void SDLUPDATE(triMesh &object);
void SDLDESTROY();
void handleKeys(unsigned char key, int x, int y);
void initGL();
void render(triMesh &object);
void loadOFF(string file, triMesh &object);
void paintObject(triMesh &object);

int main(){
	triMesh object;

	loadOFF("offFiles/sphere.off",object);
	SDLINIT();
    SDLUPDATE(object);
    SDLDESTROY();

	return 0;
}

void loadOFF(string file, triMesh &object){
	offLoad(file,object);
}

void SDLUPDATE(triMesh &object){
    int quit = 0;
    SDL_Event e;

        //While application is running
        while(!quit)
        {
            //Handle events on queue
            while(SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if(e.type == SDL_QUIT){
                    quit = 1;
                }
            }
            //Render quad
            render(object);
            
            //Update screen
            SDL_GL_SwapWindow(window);
        }
}

void render(triMesh &object){
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT); 
    paintObject(object);
    //glRotated(1,0,1,0);
}

void paintObject(triMesh &object){
	int faces = object.numberFaces();
	int point;
	int nFaces = 0;

    
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        photonTrace(500,object.maxX,object.minX,object.maxY,object.minY,object.maxZ + 2,object); 
    glEnd();
    glColor3f(255, 255, 255); //borrar 

	glBegin(GL_LINES);
    	for(int i = 0;i<faces;i++){
    		nFaces = object.faceRelation[i][0];
    		for(int j = 1;j<=nFaces;j++){
	    		point = object.faceRelation[i][j];
	    		glVertex3f(object.points[point].x(), object.points[point].y(), object.points[point].z());
    		}
            point = object.faceRelation[i][1]; //with lines necesary
            glVertex3f(object.points[point].x(), object.points[point].y(), object.points[point].z());
    	}	
    glEnd();
}

void SDLDESTROY(){
    //Destroy window 
    SDL_DestroyWindow(window);
    window = NULL;
    //Quit SDL subsystems 
    SDL_Quit(); 
}

void SDLINIT(){
    //Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    //VERSION?!?
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    //Create Window
    window = SDL_CreateWindow("Objects",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    wContext = SDL_GL_CreateContext(window);

    SDL_GL_SetSwapInterval(1);
    initGL();
}

void initGL(){
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       glClearColor(0.f, 0.f, 0.f, 1.f);
}

