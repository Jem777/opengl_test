#include <stdio.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL.h>

#include "vertex_buffer.h"

void setup_rendering() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
}

void start_rendering() {
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0, 400, 400, 0, -100, 100 );

    setup_rendering();
    glRectf(10, 20, 50, 70);
}

int handle_events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 1;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            return 1;
        }
    }
    return 0;
}

int main(void){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0){
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_WM_SetCaption("OpenGL test window", "OpenGL");
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Surface *surface = SDL_SetVideoMode(400, 400, 32, SDL_OPENGL);
    if (surface == NULL) {
        fprintf(stderr, "Failed to initialize OpenGL: %s\n", SDL_GetError());
        return 1;
    }

    GLenum err = glewInit();
    if (GLEW_OK != err) {
          /*  Problem: glewInit failed, something is seriously wrong. */
          fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
          return 1;
    }

    setup_vbo();
    SDL_GL_SwapBuffers();
    printf("OpenGL Version is %s\n", glGetString(GL_VERSION));
    while(1) {
        //start_rendering();
        //SDL_GL_SwapBuffers();
        if(handle_events() == 1) {
            SDL_Quit();
            exit(0);
        }
    }
}
