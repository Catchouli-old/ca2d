#include "gltypes/GLShaderProgram.h"

#include "resources/File.h"

#include <stdio.h>
#include <malloc.h>
#include <glm/glm.hpp>

namespace rend
{
	void GLShaderProgramDeleter(GLuint* shader)
	{
		glDeleteProgram(*shader);
		delete shader;
	};

	GLShaderProgram::GLShaderProgram(const char* vs_filename, const char* fs_filename)
        : mShaderProg(glCreateProgram())
	{
		GLShader vertexShader(GL_VERTEX_SHADER, vs_filename);
		GLShader fragmentShader(GL_FRAGMENT_SHADER, fs_filename);

        if (!vertexShader.isValid() || !fragmentShader.isValid())
        {
            fprintf(stderr, "Failed to create shader program\n");
            return;
        }

		// Attach shaders
		glAttachShader(mShaderProg.get(), vertexShader);
		glAttachShader(mShaderProg.get(), fragmentShader);

		// Link program
		glLinkProgram(mShaderProg.get());
	}

	GLShaderProgram::~GLShaderProgram()
	{
        if (mShaderProg != nullptr)
        {
            GLint currentShader;
            glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);

            if (currentShader == mShaderProg.get())
            {
                glUseProgram(0);
            }
        }
	}

	void GLShaderProgram::bind() const
	{
		glUseProgram(mShaderProg.get());
	}

	void GLShaderProgram::unbind() const
	{
		glUseProgram(0);
	}

	bool GLShaderProgram::isValid() const
	{
		return mShaderProg.get() != 0;
	}

	GLint GLShaderProgram::getAttributeLocation(const char* name) const
	{
		return glGetAttribLocation(mShaderProg.get(), name);
	}

	GLint GLShaderProgram::enableAttribute(const char* name)
	{
		GLint location = getAttributeLocation(name);

		if (location == -1)
		{
			fprintf(stderr, "Attempt to enable nonexistent attribute: %s\n", name);
		}
		else
		{
			glEnableVertexAttribArray(location);
		}

		return location;
	}

	void GLShaderProgram::disableAttribute(const char* name)
	{
		GLint location = getAttributeLocation(name);

		if (location == -1)
		{
			fprintf(stderr, "Attempt to disable nonexistent attribute: %s\n", name);
		}
		else
		{
			glEnableVertexAttribArray(location);
		}
	}

	GLint GLShaderProgram::getUniformLocation(const char* name) const
	{
		return glGetUniformLocation(mShaderProg.get(), name);
	}

	GLShaderProgram::operator GLuint() const
	{
		return mShaderProg.get();
	}

	void GLShaderProgram::setUniformInt(const char* name, const int i)
	{
		int loc = getUniformLocation(name);
		glUniform1i(loc, i);
	}

	void GLShaderProgram::setUniformFloat(const char* name, const float f)
	{
		int loc = getUniformLocation(name);
		glUniform1f(loc, f);
	}

	void GLShaderProgram::setUniformDouble(const char* name, const double d)
	{
		int loc = getUniformLocation(name);
		//glUniform1d(loc, d);
	}

	void GLShaderProgram::setUniformVector(const char* name, const glm::vec2& vector)
	{
		int loc = getUniformLocation(name);
		glUniform2f(loc, vector.x, vector.y);
	}

	void GLShaderProgram::setUniformVector(const char* name, const glm::vec3& vector)
	{
		int loc = getUniformLocation(name);
		glUniform3f(loc, vector.x, vector.y, vector.z);
	}

	void GLShaderProgram::setUniformVector(const char* name, const glm::vec4& vector)
	{
		int loc = getUniformLocation(name);
		glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
	}
	
	void GLShaderProgram::setUniformMatrix(const char* name, const glm::mat4& matrix)
	{
		int loc = getUniformLocation(name);
		glUniformMatrix4fv(loc, 1, false, (float*)&matrix);
	}
}