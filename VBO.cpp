#include "VBO.h"

VBO::VBO(std::vector<GLfloat> vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(vertices),
		vertices.data(), 
		GL_STATIC_DRAW);
}