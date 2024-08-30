#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class keyboard {

public:
	
	// keystate callncak func
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	// accessor funcs
	static bool key(int key);
	static bool keyStateChanged(int key);
	static bool keyWentUp(int key);
	static bool keyWentDn(int key);

private:

	static bool keys[];
	static bool keysStateChanged[];
};

#endif
