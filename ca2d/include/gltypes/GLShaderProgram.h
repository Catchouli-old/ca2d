#pragma once

#include "GLShader.h"
#include "GLTexture2D.h"

#include "../rendering/OpenGL.h"
#include <glm/matrix.hpp>

#include <memory>

namespace rend
{
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
		GLShaderProgram(const char* vs_filename, const char* fs_filename);

		~GLShaderProgram();

		void bind() const;
		void unbind() const;

		bool isValid() const;

		GLint getAttributeLocation(const char* name) const;
		GLint enableAttribute(const char* name);
		void disableAttribute(const char* name);

		GLint getUniformLocation(const char* name) const;

		void setUniformInt(const char* name, const int i);
		void setUniformFloat(const char* name, const float f);
		void setUniformDouble(const char* name, const double d);
		void setUniformVector(const char* name, const glm::vec2& vector);
		void setUniformVector(const char* name, const glm::vec3& vector);
		void setUniformVector(const char* name, const glm::vec4& vector);
		void setUniformMatrix(const char* name, const glm::mat4& matrix);
		void setUniformTexture(const char* name, const GLTexture2D& texture);

		operator GLuint() const;

	private:
		std::unique_ptr<GLuint, GLShaderProgramDeleter> mShaderProg;
	};
}