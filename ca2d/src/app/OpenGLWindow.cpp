#include "app/OpenGLWindow.h"

#include <iostream>

#include <SDL2/SDL.h>

namespace ca2d
{
    namespace
    {
    }

    /** Create an OpenGL window of the specified width and height */
    OpenGLWindow::OpenGLWindow(int width, int height)
    {
        createWindow(width, height);
    }

    /** Swap buffers */
    void OpenGLWindow::swap()
    {
        makeContextCurrent();
        SDL_GL_SwapWindow(mWindow.get());
    }

    /** Make the opengl context current */
    void OpenGLWindow::makeContextCurrent()
    {
        SDL_GL_MakeCurrent(mWindow.get(), mContext.get());
    }

    /** Initialise SDL and create a window */
    void OpenGLWindow::createWindow(int width, int height)
    {
        // Init SDL
        SDL_Init(SDL_INIT_EVERYTHING);

        // Create window
        SDL_Window* window = SDL_CreateWindow(
                                "",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                width,
                                height,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        if (window == nullptr)
        {
            fprintf(stderr, "Failed to create window: %s\n",
                SDL_GetError());
            exit(1);
        }

        // Store window pointer
        mWindow = std::unique_ptr<SDL_Window, SDLWindowDeleter>(window);

        // Create openGL context
        mContext = std::unique_ptr<SDL_GLContext, SDLContextDeleter>(SDL_GL_CreateContext(mWindow.get()));

        // Set atexit to clean up SDL
        atexit(SDL_Quit);
    }

    /** Set window title */
    void OpenGLWindow::setTitle(const char* title)
    {
        SDL_SetWindowTitle(mWindow.get(), title);
    }

}