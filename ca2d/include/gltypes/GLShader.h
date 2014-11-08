#ifndef RENDER_UTILS_GL_SHADER_H
#define RENDER_UTILS_GL_SHADER_H

#include "GLSharedHandle.h"
#include "GLUniqueHandle.h"
#include "../resources/File.h"

#include <memory>
#include "../OpenGL.h"

namespace rend
{
	template <typename HandleType>
	class GenericShader;

	typedef GenericShader<GLUniqueHandle> GLShader;
	typedef GenericShader<GLSharedHandle> GLSharedShader;

	bool compileShader(GLuint shader, const char* filename, const char* source);

	template <typename HandleType>
	class GenericShader
		: public HandleType
	{
	public:
		GenericShader(GLuint type, const char* filename);

        bool isValid() const;

    private:
        bool mIsValid;
	};

	inline void shaderDeleter(GLuint shader)
	{
		glDeleteShader(shader);
	};

	template <typename HandleType>
	GenericShader<HandleType>::GenericShader(GLuint type, const char* filename)
		: HandleType(glCreateShader(type), shaderDeleter)
	{
		// Read files
		File file(filename);

		// Return if file read failed
		if (!file.isLoaded())
		{
            mIsValid = false;

            fprintf(stderr, "Failed to read shader source: %s\n", filename);

			return;
		}

		// Compile shaders
		compileShader((*this), filename, file.getContents().c_str());

		// Return if compilation failed for either shader
		if ((GLuint)(*this) == 0)
        {
            mIsValid = false;

            fprintf(stderr, "Failed to compile shader: %s\n", filename);

            return;
        }

        mIsValid = true;
	}

    template <typename HandleType>
    inline bool GenericShader<HandleType>::isValid() const
    {
        return mIsValid;
    }
}

#endif /* RENDER_UTILS_GL_SHADER_H */