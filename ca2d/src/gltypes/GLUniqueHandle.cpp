#include "gltypes/GLUniqueHandle.h"

namespace rend
{
	GLUniqueHandle::GLUniqueHandle(GLuint handle, SH_DeleteFunc deleteFunc)
	{
		mUniqueHandle = std::unique_ptr<GLuint, Deleter>(handle, Deleter(deleteFunc));
	}

	GLUniqueHandle::operator GLuint() const
	{
		return mUniqueHandle.get();
	}

	void GLUniqueHandle::dispose(GLuint* i, SH_DeleteFunc deleteFunc)
	{
		// Dispose i
		deleteFunc(*i);

		// Delete i
		delete i;
	}

	GLUniqueHandle::Deleter::Deleter()
		: mDeleteFunc(nullptr)
	{

	}

	GLUniqueHandle::Deleter::Deleter(SH_DeleteFunc deleteFunc)
		: mDeleteFunc(deleteFunc)
	{

	}

	void GLUniqueHandle::Deleter::operator()(GLuint shader)
	{
		// Call dispose handler
		mDeleteFunc(shader);
	}
}