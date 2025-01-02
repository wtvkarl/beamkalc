#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Triangle.h"
#include "Shader.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


int main()
{
	// ----- boilerplate start ----- //
	if (!glfwInit())
	{
		std::cout << "failed to initialize GLFW." << "\n";
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(
		800,
		800,
		"beamkalc v1.0 by karl villapacibe",
		NULL, NULL
	);

	if (window == NULL)
	{
		std::cout << "failed to create window." << "\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	// ----- boilerplate end ----- //

	glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	//test area

	std::vector<GLuint> indices = {0,1,2};

	Triangle tri = Triangle();
	tri.addVertex(0.5, -0.5, 1);
	tri.addVertex(0.5, 0.5, 1);
	tri.addVertex(-0.5, -0.5, 1);
	tri.printCoords();

	VAO vao;

	VBO vbo(tri.vertices);
	EBO ebo(indices);

	vao.linkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(GLfloat), (void*)0);
	vao.unbind();
	vbo.unbind();
	ebo.unbind();
	

	Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

	while (!glfwWindowShouldClose(window))
	{
		shaderProgram.activate();
		vao.bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}