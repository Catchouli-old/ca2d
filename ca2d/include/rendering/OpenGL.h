#pragma once

/* Include the relevant libraries for opengl functionality on this platform */

#ifdef EMSCRIPTEN
    #include <GLES2/gl2.h>
    #define GL_GLEXT_PROTOTYPES 1
    #include <GLES2/gl2ext.h>
    #include <emscripten.h>
    #include <iostream>
    #include <cstdlib>
    #include <SDL.h>
    #include <SDL_image.h>
#else
    #include <gl/glew.h>
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>
#endif