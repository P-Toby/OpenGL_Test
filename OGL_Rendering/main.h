#ifndef MAIN_H
#define MAIN_H

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLuint ShaderMasterTutorial();
GLuint ShaderMasterTwo();
GLuint ShaderMasterTwo(bool Orange);
GLuint FragmentMasterOrange();
GLuint FragmentMasterYellow();

int tutorialRender();
int assignmentOne();
int assigmentTwo();
#endif