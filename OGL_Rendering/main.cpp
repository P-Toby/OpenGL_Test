#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <stdio.h>  
#include <stdlib.h>
#include <iostream>
#include "math_3d.h"
#include "main.h"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	//Define window height and width and then create the window
	GLint wWidth = 1024;
	GLint wHeight = 768;
	GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, "OpenGL", nullptr, nullptr);

	//Check if window created successfully
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//Set openGL window size (Can be made smaller than GLFW window)
	glViewport(0, 0, wWidth, wHeight);

	//Test dot
	Vector3f Verts[1];
	Verts[0] = Vector3f(0.0f, 0.0f, 0.0f);

	//2D Triangle (z coordinates are zero)
	GLfloat triangle[] = 
	{
		//x		y		z
		-0.5f,  -0.5f,	0.0f,
		0.5f,  -0.5f,	0.0f,
		0.0f,   0.5f,	1.0f
	};
	
	//Create Vector Object Buffer
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	

	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwSetKeyCallback(window, key_callback); //Close window if escape pressed
		glfwPollEvents();

		// Rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the buffers
		glfwSwapBuffers(window);
	}
	
	//Cleanup memory
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

}