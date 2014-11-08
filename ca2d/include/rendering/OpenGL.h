#pragma once

#ifdef EMSCRIPTEN
#include <GLES2/gl2.h>
#define GL_GLEXT_PROTOTYPES 1
#include <GLES2/gl2ext.h>
#include <emscripten.h>
#include <iostream>
#include <cstdlib>
#include <SDL.h>
#else
#include <gl/glew.h>
#include <SDL/SDL.h>
#endif