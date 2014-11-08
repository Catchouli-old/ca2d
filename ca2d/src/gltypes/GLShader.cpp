#include "gltypes/GLShader.h"

#include "resources/File.h"

namespace rend
{
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
}