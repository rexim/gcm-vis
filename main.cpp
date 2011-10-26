#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include "states.hpp"

// #define SAVE_FRAMES
#define WIDTH 800
#define HEIGHT 600
#define TICK_MSECS 10

using namespace std;

State *state = new Ready(1.5f, 0.6f, 1000);
// State *state = new Ready(1.0f, 1.4142135623730951f, 1000);
int filenameCounter = 0;

void saveScreen(const char *filename)
{
    SDL_Surface *image;
    SDL_Surface *temp;
    SDL_Surface *screen = SDL_GetVideoSurface();
    int w = screen->w;
    int h = screen->h;

    image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 24,
                                 0x0000FF, 0x00FF00, 0xFF0000, 0x000000);
    temp = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 24,
                                0x0000FF, 0x00FF00, 0xFF0000, 0x000000);

    glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    for(int idx = 0; idx < h; idx++)
    {
        memcpy((unsigned char*)(temp->pixels) + 3 * w * idx,
               (unsigned char*)(image->pixels) + 3 * w * (h - idx),
               3 * w);
    }
    memcpy(image->pixels, temp->pixels, w * h * 3);
    SDL_SaveBMP(image, filename);
    SDL_FreeSurface(image);
    SDL_FreeSurface(temp);
}

void nextFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);

    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0);

    for(int x = -200; x <= 200; x += 5) {
        glVertex2f(x * 0.01f, -0.01f);
        glVertex2f(x * 0.01f, 0.01f);
    }

    glEnd();
    
    glLineWidth(6.0);
    State *nextState = state->tick(TICK_MSECS);

    if(state != nextState) {
        delete state;
        SDL_WM_SetCaption(nextState->name().c_str(), 0);
    }

    state = nextState;


#ifdef SAVE_FRAMES
    ostringstream oss;
    oss << "frame" << filenameCounter++ << ".bmp";
    saveScreen(oss.str().c_str());
#endif // SAVE_FRAMES

    SDL_Delay(TICK_MSECS);
    SDL_GL_SwapBuffers();
}

void initOpenGL()
{
    glLineWidth(1.0);
}

void handleEvents(bool &quit)
{
    SDL_Event event;

    while(!quit && SDL_PollEvent(&event))
        switch(event.type) {
        case SDL_QUIT:
            quit = true;
            break;

        case SDL_KEYDOWN:
            quit = event.key.keysym.sym == SDLK_ESCAPE;
            break;
        }
}

void startLoop()
{
    bool quit = false;

    while(!quit) {
        handleEvents(quit);
        nextFrame();
    }
}

void fail(const string &message)
{
    cerr << message << endl;
    delete state;
    SDL_Quit();
    exit(1);
}

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        fail(string("ERROR: cannot initialize SDL: ") + SDL_GetError());

    if(SDL_SetVideoMode(WIDTH, HEIGHT, 24, SDL_OPENGL | SDL_DOUBLEBUF) == NULL)
        fail(string("ERROR: cannot set video mode: ") + SDL_GetError());

    SDL_WM_SetCaption(state->name().c_str(), 0);

    initOpenGL();
    startLoop();

    delete state;
    SDL_Quit();

    return 0;
}
