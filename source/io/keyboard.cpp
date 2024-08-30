#include "keyboard.h"

// private
bool keyboard::keys[GLFW_KEY_LAST] = { 0 };
bool keyboard::keysStateChanged[GLFW_KEY_LAST] = { 0 };

// keystate callback
void keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action != GLFW_RELEASE) {

		if (!keys[key]) {

			keys[key] = true;
		}
	}
	else {

		keys[key] = false;
	}

	keysStateChanged[key] = action != GLFW_REPEAT;
}

// accessor funcs
bool keyboard::key(int key) {

	return keys[key];
}

bool keyboard::keyStateChanged(int key) {

	bool retval = keysStateChanged[key];
	keysStateChanged[key] = false;

	return retval;
}

bool keyboard::keyWentUp(int key) {

	return !keys[key] && keyStateChanged(key);
}

bool keyboard::keyWentDn(int key) {

	return keys[key] && keyStateChanged(key);
}
