// Copyright (c) 2011 by rexim
// 
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>
#include <sstream>
#include <windows.h>
#include <SDL.h>
#include <GL/gl.h>
#include "states.hpp"

#define WIDTH 400
#define HEIGHT 200
#define TICK_MSECS 20

using namespace std;

State *state = new Ready(1.5f, 0.6f, 1000);
// State *state = new Ready(1.0f, 1.4142135623730951, 1000);
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

    // Horizontal Axe ////////////////////
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
    
    // Next State ////////////////////
    glLineWidth(6.0);
    State *nextState = state->tick(TICK_MSECS);

    if(state != nextState) {
        delete state;
        SDL_WM_SetCaption(nextState->name().c_str(), 0);
    }

    state = nextState;

    // Save Frames ////////////////////
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

int main(int argc, char **argv)
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
