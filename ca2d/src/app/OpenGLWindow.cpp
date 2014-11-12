#include "app/OpenGLWindow.h"

#include <iostream>

#include <SDL/SDL.h>

namespace ca2d
{

    /* Create an OpenGL window of the specified width and height */
    OpenGLWindow::OpenGLWindow(int width, int height)
    {
        // Initialise SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cerr << "Failed to initialise SDL: " << SDL_GetError() << std::endl;
        }

        // Set video mode
        mSDLsurface = SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);

        if (mSDLsurface == nullptr)
        {
            std::cerr << "Failed to set video mode: " << SDL_GetError() << std::endl;
        }

        // Set atexit to clean up SDL
        atexit(SDL_Quit);
    }

    /* Swap buffers */
    void OpenGLWindow::swap()
    {
        SDL_GL_SwapBuffers();
    }

}