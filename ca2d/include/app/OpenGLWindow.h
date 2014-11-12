#pragma once

struct SDL_Surface;

namespace ca2d
{
    class OpenGLWindow
    {
    public:

        /** Create an OpenGL window of the specified width and height */
        OpenGLWindow(int width, int height);

        /** Swap buffers */
        void swap();

    private:

        /** SDL state */
        SDL_Surface* mSDLsurface;

    };
}