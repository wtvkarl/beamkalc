#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Triangle.h"
#include "VBO.h"
#include "Shader.h"

int main()
{
	// ----- boilerplate start ----- //
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(
		800,
		800,
		"beamkalc v1.0",
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

	Triangle tri = Triangle();
	tri.addVertex(0.5, -0.5, 1);
	tri.addVertex(0.5, 0.5, 1);
	tri.addVertex(-0.5, -0.5, 1);
	tri.printCoords();

	Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	VBO VBO1(tri.vertices);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1.ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri.vertices), tri.vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram.ID);
	glBindVertexArray(VAO);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glDrawArrays(GL_TRIANGLES, 0, tri.vertices.size());
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}