#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>


int main(void){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0){
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_WM_SetCaption("OpenGL test window", "OpenGL");
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Surface *surface = SDL_SetVideoMode(400, 400, 32, SDL_OPENGL);

    SDL_Event event;

    while(1) {
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0, 400, 400, 0, -1, 1 );

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 0.0f, 0.0f);
        glRectf(10, 20, 50, 70);
        SDL_GL_SwapBuffers();
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                SDL_Quit();
                exit(0);
            }
        }
    }
}
