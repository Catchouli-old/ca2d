#include "gltypes/GLShaderProgram.h"

#include "resources/File.h"

#include <stdio.h>
#include <malloc.h>
#include <glm/glm.hpp>

namespace ca2d
{

    /** Creates and links a shader program with a vertex and fragment shader */
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

    /** Unbinds this shader if it is bound, and destroys it */
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

    /** Binds this shader program */
	void GLShaderProgram::bind() const
	{
		glUseProgram(mShaderProg.get());
	}

    /** Unbinds this shader program */
	void GLShaderProgram::unbind() const
	{
		glUseProgram(0);
	}

    /** Whether this shader program has compiled and linked successfully */
	bool GLShaderProgram::isValid() const
	{
		return mShaderProg.get() != 0;
	}

    /** Get the location of an attribute */
	GLint GLShaderProgram::getAttributeLocation(const char* name) const
	{
		return glGetAttribLocation(mShaderProg.get(), name);
	}

    /** Enable an attribute and get its location */
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

    /** Disable an attribute */
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

    /** Get the location of a uniform */
	GLint GLShaderProgram::getUniformLocation(const char* name) const
	{
		return glGetUniformLocation(mShaderProg.get(), name);
	}

    /** Upload an int uniform */
	void GLShaderProgram::setUniformInt(const char* name, const int i)
	{
		int loc = getUniformLocation(name);
		glUniform1i(loc, i);
	}

    /** Upload a float uniform */
	void GLShaderProgram::setUniformFloat(const char* name, const float f)
	{
		int loc = getUniformLocation(name);
		glUniform1f(loc, f);
	}

    /** Upload a vec2 uniform */
	void GLShaderProgram::setUniformVector(const char* name, const glm::vec2& vector)
	{
		int loc = getUniformLocation(name);
		glUniform2f(loc, vector.x, vector.y);
	}

    /** Upload a vec3 uniform */
	void GLShaderProgram::setUniformVector(const char* name, const glm::vec3& vector)
	{
		int loc = getUniformLocation(name);
		glUniform3f(loc, vector.x, vector.y, vector.z);
	}

    /** Upload a vec4 uniform */
	void GLShaderProgram::setUniformVector(const char* name, const glm::vec4& vector)
	{
		int loc = getUniformLocation(name);
		glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
	}

    /** Upload a mat4 uniform */
	void GLShaderProgram::setUniformMatrix(const char* name, const glm::mat4& matrix)
	{
		int loc = getUniformLocation(name);
		glUniformMatrix4fv(loc, 1, false, (float*)&matrix);
	}
}