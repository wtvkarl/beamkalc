#include "VBO.h"

VBO::VBO(std::vector<GLfloat> vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(GLfloat), //multiply by sizeof data type used
		vertices.data(),
		GL_STATIC_DRAW
	);
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::discard()
{
	glDeleteBuffers(1, &ID);
}