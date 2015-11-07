#pragma once
#ifndef HELLOTRIANGLE_AND_ASSIGNMENTS_H
#define HELLOTRIANGLE_AND_ASSIGNMENTS_H

GLuint ShaderMasterTutorial();
GLuint ShaderMasterTwo();
GLuint ShaderMasterTwo(bool Orange);
GLuint FragmentMasterOrange();
GLuint FragmentMasterYellow();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int tutorialRender();
int assignmentOne();
int assigmentTwo();
#endif