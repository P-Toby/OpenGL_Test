//Include GLEW  
#include <GL\glew.h>

//Include GLFW  
#include <GLFW\glfw3.h>  

//Include the standard C++ headers  
#include <stdio.h>  
#include <stdlib.h>
#include <iostream>
#include "main.h"
#include "hellotriangle_and_assignments.h"
#include "shaderPractice.h"


int main()
{
	//tutorialRender();
	//assignmentOne();
	//assigmentTwo();
	//shaderPractice();
	texturePractice();

	//Cleanup memory
	glfwTerminate();
	return 0;
}

