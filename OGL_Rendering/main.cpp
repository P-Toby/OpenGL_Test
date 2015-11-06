#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>  
#include <stdlib.h>
#include <iostream>

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

	//2D Triangle (z coordinates are zero)
	GLfloat triangle[] = {
		//x		y		z
		-0.5f,  -0.5f,	0.0f,
		0.5f,  -0.5f,	0.0f,
		0.0f,   0.5f,	1.0f
	};

	//Cleanup memory
	glfwTerminate();
	return 0;
}