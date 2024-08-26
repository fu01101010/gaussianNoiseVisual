#ifndef SCREEN_H
#define SCREEN_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class screen {

public:

	static unsigned SCR_WIDTH;
	static unsigned SCR_HEIGHT;

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	screen();

	bool init();

	void setParameters();

	// main 
	void update();
	void newFrame();

	// window closing accessor and modifier func
	bool shouldClose();
	void setShouldClose(bool shouldClose);

private:
	GLFWwindow* window;
};

#endif
