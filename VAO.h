#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	GLuint ID;
	VAO();

	void linkAttrib(
		VBO& vbo,
		GLuint layout,
		GLuint numComponents,
		GLenum type,
		GLsizeiptr stride,
		void* offset
	);

	void bind();
	void unbind();
	void discard();
};

#endif VAO_CLASS_H