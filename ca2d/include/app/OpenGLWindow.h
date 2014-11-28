#pragma once

#include <memory>
#include <SDL2/SDL.h>

namespace ca2d
{
    /** A deleter struct for SDL_Window unique_ptrs */
    struct SDLWindowDeleter
    {
        typedef SDL_Window* pointer;

        void operator()(SDL_Window* window)
        {
            SDL_DestroyWindow(window);
        }
    };

    /** A deleter struct for SDL_Context unique_ptrs */
    struct SDLContextDeleter
    {
        typedef SDL_GLContext pointer;

        void operator()(SDL_GLContext context)
        {
            SDL_GL_DeleteContext(context);
        }
    };

    /** An class that creates a window with an OpenGL context */
    class OpenGLWindow
    {
    public:

        /** Create an OpenGL window of the specified width and height */
        OpenGLWindow(int width, int height);

        /** Swap buffers */
        void swap();

        /** Set window title */
        void setTitle(const char* title);

        /** Make the opengl context current */
        void makeContextCurrent();

    private:

        /** Initialise SDL and create a window */
        void createWindow(int width, int height);

        /** SDL window */
        std::unique_ptr<SDL_Window, SDLWindowDeleter> mWindow;

        /** SDL renderer */
        std::unique_ptr<SDL_GLContext, SDLContextDeleter> mContext;

    };
}