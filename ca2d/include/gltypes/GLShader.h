#pragma once

#include "../resources/File.h"

#include <memory>
#include "../rendering/OpenGL.h"

namespace rend
{
    bool compileShader(GLuint shader, const char* filename, const char* source);

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
        GLShader(GLuint type, const char* filename);

        bool isValid() const;

        operator GLuint() const;

    private:
        std::unique_ptr<GLuint, GLShaderDeleter> mShader;

        bool mIsValid;
	};

    inline bool GLShader::isValid() const
    {
        return mIsValid;
    }

    inline GLShader::operator GLuint() const
    {
        return mShader.get();
    }
}