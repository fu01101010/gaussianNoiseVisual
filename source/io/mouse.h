#ifndef MOUSE_H
#define MOUSE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class mouse {

public:

	// mouse state callback funcs
	static void cursorPositionCallback(GLFWwindow* window, double _x, double _y);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseWheelCallback(GLFWwindow* window, double _dx, double _dy);

	// accessor funcs
	static double getMouseX();
	static double getMouseY();

	static double getDX();
	static double getDY();

	static double getScrollDX();
	static double getScrollDY();

	static bool button(int button);
	static bool buttonStateChanged(int button);
	static bool buttonWentUp(int button);
	static bool buttonWentDn(int button);

private:

	static double X;
	static double Y;

	static double lastX;
	static double lastY;

	static double DX;
	static double DY;

	static double scrollDX;
	static double scrollDY;

	static bool firstMouseMovement;

	static bool buttons[];
	static bool buttonsStateChanged[];
};

#endif
