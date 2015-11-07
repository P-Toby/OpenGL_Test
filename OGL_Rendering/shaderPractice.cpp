//Include GLEW  
#include <GL\glew.h>

//Include GLFW  
#include <GLFW\glfw3.h>  

//Include the standard C++ headers  
#include <stdio.h>  
#include <stdlib.h>
#include <iostream>

#include "shaderPractice.h"
#include "keycallback.h"

int shaderPractice()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Define window size
	GLint wWidth = 1024;
	GLint wHeight = 768;

	//Create GLFW window
	GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, "OpenGLTest", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//Set openGL window size (Can be made smaller than GLFW window)
	glViewport(0, 0, wWidth, wHeight);

	GLfloat triangle[] = {
		//x y z
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 1.0f
	};

	//Create VBO and send triangle
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	//Create VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0); //Unbind VAO until ready to render



						  //Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwSetKeyCallback(window, key_callback); //Close window if escape pressed
		glfwPollEvents();

		// Rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//Draw

		// Swap the buffers
		glfwSwapBuffers(window);
	}

	return 0;
}

GLuint createShaderProgram()
{

	return 0;
}