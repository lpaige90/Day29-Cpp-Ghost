#ifndef GHOST_H
#define GHOST_H
#include "D:\GLFW\include\windows\glfw3.h"
#include "D:\SOIL2\include\SOIL2\SOIL2.h"
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "soil2-debug.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

extern double mouseX, mouseY;
extern bool click;

class Ghost {
	const char *file;

	GLuint loadGhost();
	void drawGhost(GLuint texture, GLfloat x, GLfloat y);

	public:
		Ghost(const char *filename);
		void showGhost(double x, double y);
		
};

#endif