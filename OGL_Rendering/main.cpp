//Include GLEW  
#include <GL\glew.h>

//Include GLFW  
#include <GLFW\glfw3.h>  

//Include the standard C++ headers  
#include <stdio.h>  
#include <stdlib.h>
#include <iostream>

#include "main.h"

int main()
{
	bool useWireFrame = false; //Set to true in order to render in wireframe

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//2D Triangle (z coordinates are zero)
	GLfloat triangle[] = {
		//x		y		z
		-0.5f,  -0.5f,	0.0f,
		0.5f,  -0.5f,	0.0f,
		0.0f,   0.5f,	1.0f,
	};

	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	GLuint indices[] = { 
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};

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

	/////////////////////////////////////////////////////////
	//Create Vertex Buffer Object and send triangle to buffer
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	///Create shader program
	GLuint shaderProgram = ShaderMaster();

	//Linking vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	

	/////////////////////////////////////////////////////
	//Element Buffer Object
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//Vertex array object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// 1. Bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. Copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. Copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 3. Then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// 4. Unbind VAO (NOT the EBO)
	glBindVertexArray(0);

	if (useWireFrame)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	
	//Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwSetKeyCallback(window, key_callback); //Close window if escape pressed
		glfwPollEvents();

		// Rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap the buffers
		glfwSwapBuffers(window);
	}

	//Cleanup memory
	glfwTerminate();
	return 0;
}

GLuint ShaderMaster()
{
	//Create Vertex Shader////////////////////////////////
	const GLchar* vertexShaderSource = "#version 330 core\n layout(location = 0) in vec3 position; void main(){gl_Position = vec4(position.x, position.y, position.z, 1.0);}";

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	///////////////////////////////////////////////////////

	//Create Fragment shader///////////////////////////////
	const GLchar* fragmentShaderSource = "#version 330 core\n out vec4 color; void main(){color = vec4(1.0f, 0.0f, 0.0f, 1.0f);}";
	
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application
	if ((key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) || (GLFW_KEY_F10 && action == GLFW_PRESS))
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}