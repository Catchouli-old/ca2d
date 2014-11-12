#pragma once

#include "GLShader.h"
#include "GLTexture2D.h"

#include "../rendering/OpenGL.h"
#include <glm/matrix.hpp>

#include <memory>

namespace ca2d
{

    /** A deleter in charge of cleaning up opengl program handles and defining the handle type */
    struct GLShaderProgramDeleter
    {
        typedef GLuint pointer;

        void operator()(GLuint shaderProgram)
        {
            glDeleteProgram(shaderProgram);
        }
    };

	class GLShaderProgram
	{
	public:

        /** Creates and links a shader program with a vertex and fragment shader */
		GLShaderProgram(const char* vs_filename, const char* fs_filename);

        /** Unbinds this shader if it is bound, and destroys it */
		~GLShaderProgram();

        /** Binds this shader program */
		void bind() const;

        /** Unbinds this shader program */
		void unbind() const;

        /** Whether this shader program has compiled and linked successfully */
		bool isValid() const;

        /** Get an attribute's location */
		GLint getAttributeLocation(const char* name) const;

        /** Enable an attribute and get its location */
		GLint enableAttribute(const char* name);

        /** Disable an attribute */
		void disableAttribute(const char* name);

        /** Uniform access */
		GLint getUniformLocation(const char* name) const;

        /** Uniform upload functions */
		void setUniformInt(const char* name, const int i);
		void setUniformFloat(const char* name, const float f);
		void setUniformVector(const char* name, const glm::vec2& vector);
		void setUniformVector(const char* name, const glm::vec3& vector);
		void setUniformVector(const char* name, const glm::vec4& vector);
		void setUniformMatrix(const char* name, const glm::mat4& matrix);

        /** Allows this object to be passed into opengl calls directly */
		operator GLuint() const;

	private:

        /** The unique pointer that is responsible for ownership of the opengl handle */
        std::unique_ptr<GLuint, GLShaderProgramDeleter> mShaderProg;

	};
}