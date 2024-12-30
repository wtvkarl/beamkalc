#ifndef TRIANGLE_CLASS_H
#define TRIANGLE_CLASS_H

#include <vector>
#include <iostream>
#include <string>
#include <glad/glad.h>

class Triangle
{
public:
	Triangle();
	std::vector <GLfloat> vertices;
	void addVertex(GLfloat x, GLfloat y, GLfloat z);
	void printCoords();
};

#endif TRIANGLE_CLASS_H