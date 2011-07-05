#include <stdio.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL.h>

#include "vertex_buffer.h"

void setup_rendering() {
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glFrustum(0, 20, 20, 0, 0, 10);
    //glRotatef()
    //glTranslatef(-1.0f, 0.0f, 0.0f);
    glScalef(0.3f, 0.3f, 0.3f);
    glRotatef(90, -1,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
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

    printf("OpenGL Version is %s\n", glGetString(GL_VERSION));
    setup_rendering();
    buffer_t buffer = create_vbo(10, 10);
    while(1) {
        //glScalef(1.0, 1.0, 1.1f);
        glRotatef(10, 0,0,1);
        glColor3f(1.0f, 0.0f, 0.0f);
        draw_vbo(buffer);
        glColor3f(1.0f, 1.0f, 0.0f);
        draw_vbo_raw(buffer);
        SDL_GL_SwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_Delay(500);
        if(handle_events() == 1) {
            destroy_vbo(buffer);
            SDL_Quit();
            exit(0);
        }
    }
}
