#ifndef VBO_CLASS_H
#define VBO_CLASS_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class VBO
{
public:
	GLuint ID;
	VBO();
	void bind();
	void unbind();
	void discard();
};


#endif VBO_CLASS_H