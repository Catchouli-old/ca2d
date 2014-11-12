#include "gltypes/GLShader.h"

#include "resources/File.h"

namespace ca2d
{

    /** Compile a glsl shader */
	bool compileShader(GLuint shader, const char* filename, const char* source)
	{
		GLint compiled;

		// Set shader source
		glShaderSource(shader, 1, (const GLchar**)&source, NULL);

		// Compile shader
		glCompileShader(shader);

		// Get compile status
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			char* buf;
			GLint length;

			// Get error length
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			// Allocate memory
			buf = (char*)malloc(length);
			glGetShaderInfoLog(shader, length, &length, buf);

			fprintf(stderr, "Failed to compile shader %s: \n%s", filename, buf);

			// Cleanup
			free(buf);
			glDeleteShader(shader);

			return false;
		}

		return true;
    }

    /** Creates and attemptps to compile a glsl shader */
    GLShader::GLShader(GLuint type, const char* filename)
        : mShader(glCreateShader(type))
    {
        // Read files
        File file(filename);

        // Return if file read failed
        if (!file.exists())
        {
            mIsValid = false;

            fprintf(stderr, "Failed to read shader source: %s\n", filename);

            return;
        }

        // Compile shaders
        compileShader(mShader.get(), filename, file.getContents().c_str());

        // Return if compilation failed for either shader
        if (mShader.get() == 0)
        {
            mIsValid = false;

            fprintf(stderr, "Failed to compile shader: %s\n", filename);

            return;
        }

        mIsValid = true;
    }
}