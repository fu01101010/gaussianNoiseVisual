#include "mouse.h"

double mouse::x = 0;
double mouse::y = 0;

double mouse::lastX = 0;
double mouse::lastY = 0;

double mouse::dx = 0;
double mouse::dy = 0;

double mouse::scrollDX = 0;
double mouse::scrollDY = 0;

bool mouse::firstMouseMovement = true;

bool mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool mouse::buttonsStateChanged[GLFW_MOUSE_BUTTON_LAST] = { 0 };

// mouse state callback funcs
void mouse::cursorPosCallback(GLFWwindow* window, double _x, double _y) {

	x = _x;
	y = _y;

	if (firstMouseMovement) {

		lastX = x;
		lastY = y;
		firstMouseMovement = false;
	}

	dx = x - lastX;
	dy = lastY - y;

	lastX = x;
	lastY = y;
}

void mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

	if (action != GLFW_RELEASE) {

		if (!buttons[button]) {

			buttons[button] = true;
		}
	}
	else {

		buttons[button] = false;
	}

	buttonsStateChanged[button] = action != GLFW_REPEAT;
}

void mouse::mouseWheelCallback(GLFWwindow* window, double _dx, double _dy) {

	scrollDX = _dx;
	scrollDY = _dy;
}

// accessor funcs
double mouse::getMouseX() {

	return x;
}

double mouse::getMouseY() {

	return y;
}

double mouse::getDX() {

	double _dx = dx;
	dx = 0;

	return _dx;
}

double mouse::getDY() {

	double _dy = dy;
	dy = 0;

	return _dy;
}

double mouse::getScrollDX() {

	double _dx = scrollDX;
	scrollDX = 0;

	return _dx;
}

double mouse::getScrollDY() {

	double _dy = scrollDY;
	scrollDY = 0;

	return _dy;
}

bool mouse::button(int button) {

	return buttons[button];
}

bool mouse::buttonStateChanged(int button) {

	bool retval = buttonsStateChanged[button];
	buttonsStateChanged[button] = false;

	return retval;
}

bool mouse::buttonWentUp(int button) {

	return !buttons[button] && buttonStateChanged(button);
}

bool mouse::buttonWentDn(int button) {

	return buttons[button] && buttonStateChanged(button);
}
