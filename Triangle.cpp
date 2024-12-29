#include "Triangle.h"

Triangle::Triangle(){}

void Triangle::addVertex(GLfloat x, GLfloat y, GLfloat z)
{
	if (vertices.size() == 9)
		return;

	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void Triangle::printCoords()
{
	for (int i = 0; i < vertices.size(); i += 3) 
	{
		std::cout << "[" << vertices.at(i) << ", " <<
			vertices.at(i + 1) << ", " << vertices.at(i + 2) << "]\n";
	}
}