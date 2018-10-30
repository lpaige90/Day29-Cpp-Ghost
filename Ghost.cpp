#include "Ghost.h"

double mouseX, mouseY;
bool click;

Ghost::Ghost(const char *filename) {
	file = filename;
}

GLuint Ghost::loadGhost() {
	GLuint texture = SOIL_load_OGL_texture(
		this->file,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
	);
	return texture;
}

void Ghost::drawGhost(GLuint texture, GLfloat x, GLfloat y) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-0.084f + x, -0.08f + y);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.084f + x, -0.08f + y);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.084f + x, 0.08f + y);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-0.084f + x, 0.08f + y);
	glEnd();
}

void Ghost::showGhost(double x, double y) {
	GLuint texture;
	texture = this->loadGhost();

	if (0 == texture) {
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		exit(EXIT_FAILURE);
	}

	GLfloat xPos = (GLfloat)x;
	GLfloat yPos = (GLfloat)y;

	this->drawGhost(texture, xPos, yPos);
}