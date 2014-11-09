#pragma once

#include "../resources/File.h"

#include <memory>
#include "../rendering/OpenGL.h"

namespace ca2d
{

    /* Compile a glsl shader */
    bool compileShader(GLuint shader, const char* filename, const char* source);

    /* The deleter struct responsible for defining the handle type and cleaning up opengl shaders */
    struct GLShaderDeleter
    {
        typedef GLuint pointer;

        void operator()(GLuint shader)
        {
            glDeleteShader(shader);
        }
    };

    class GLShader
	{
	public:

        /* Creates and attemptps to compile a glsl shader */
        GLShader(GLuint type, const char* filename);

        /* Returns whether or not this shader compiled successfully */
        bool isValid() const;

        /* Allows this shader to be passed into opengl calls directly */
        operator GLuint() const;

    private:

        /* Responsible for the ownership of the opengl handle for this shader */
        std::unique_ptr<GLuint, GLShaderDeleter> mShader;

        /* Whetther or not this shader compiled successfully */
        bool mIsValid;

	};

    /* Returns whether or not this shader compiled successfully */
    inline bool GLShader::isValid() const
    {
        return mIsValid;
    }

    /* Allows this shader to be passed into opengl calls directly */
    inline GLShader::operator GLuint() const
    {
        return mShader.get();
    }
}