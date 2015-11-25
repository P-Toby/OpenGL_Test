//Include GLEW  
#include <GL\glew.h>

//Include GLFW  
#include <GLFW\glfw3.h>  

//Include the standard C++ headers  
#include <stdio.h>  
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "shaderPractice.h"
#include "keycallback.h"

#include "bthassignment.h"

int bthAssignment()
{
	///Create the window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

	///Render a quad with indices
	GLfloat vertices[] = {
		//Positions
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	GLuint indices[] = {
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};

	///VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); //Important we bind the VAO first
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	///VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	///Create EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind VBO for now
	glBindVertexArray(0); //Unbind VAO as well until we are ready to use it

	GLuint shaderProgram = createSP();

	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwSetKeyCallback(window, key_callback); //Close window if escape pressed
		glfwPollEvents();

		// Rendering commands here
		GLfloat timeValue = glfwGetTime();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); //Unbind VAO when done

		// Swap the buffers
		glfwSwapBuffers(window);
	}

	//Delete the buffers when we are done using them
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return 0;
}

//Create shaderprogram
GLuint createSP()
{
	GLint success;
	GLchar infoLog[512];

	//Read Vertex Shader
	std::string readSource = readShaderCode("VertexShaderSource.glsl");
	const GLchar* vertexShaderSource = readSource.c_str();

	//Create Vertex shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//////////////////////

	//Read Fragment shader
	readSource = readShaderCode("FragmentShaderSource.glsl");
	const GLchar* fragmentShaderSource = readSource.c_str();

	//Create Fragment shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	///////////////////////////////////////////////////////

	//Create Shader program////////////////////////////////
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//After linking we can delete the shaders since they are contained in the shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	///////////////////////////////////////////////////////

	return shaderProgram;
}

std::string readShaderSource(const char* fileName)
{
	//Read from file
	std::ifstream inFile;
	inFile.open(fileName);
	if (inFile.fail())
	{
		std::cout << "GLSL Shader not found! " << fileName << std::endl;
	}

	return std::string(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>());
}