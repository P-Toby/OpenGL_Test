#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <stdio.h>  
#include <stdlib.h>
#include <iostream>
#include "math_3d.h"

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

	//2D Triangle (z coordinates are zero)
	GLfloat triangle[] = 
	{
		//x		y		z
		-0.5f,  -0.5f,	0.0f,
		0.5f,  -0.5f,	0.0f,
		0.0f,   0.5f,	1.0f
	};
	
	//Cleanup memory
	glfwTerminate();
	return 0;
}