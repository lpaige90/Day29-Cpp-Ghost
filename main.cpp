#include "Ghost.h"
#include <memory>
#include <iostream>

static void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	click = false;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && GLFW_PRESS) {
		click = true;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		mouseX = ((mouseX - 800.0 / 2.0) / 400.0) - (0.1f);
		mouseY = (-(mouseY - 600.0 / 2.0) / 300.0) + (0.1f);
	}
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	click = false;
	mouseX = ((xpos - 800.0 / 2.0) / 400.0) - (0.1f);
	mouseY = (-(ypos - 600.0 / 2.0) / 300.0) + (0.1f);
}

int main() {
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 600, "Boo!", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	int width;
	int height;
	float ratio;

	glfwMakeContextCurrent(window);

	//Set callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);

	std::unique_ptr<Ghost> boo(new Ghost("../boo.png"));
	std::unique_ptr<Ghost> hide(new Ghost("../hide.png"));

	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);//Buffer enabled for color writing

		ratio = (float)width / (float)height;

		glMatrixMode(GL_PROJECTION);//Projection matrix stack
		glLoadIdentity();
		glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);//Projection

		glMatrixMode(GL_MODELVIEW);//Modelview matrix stack
		glLoadIdentity();

		if (click == false) {
			boo->showGhost(mouseX, mouseY);
		}
		else if (click == true) {
			hide->showGhost(mouseX, mouseY);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}