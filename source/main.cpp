#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../source/graphics/shader.h"
#include "../source/graphics/light.h"

#include "../source/io/mouse.h"
#include "../source/io/keyboard.h"
#include "../source/io/screen.h"
#include "../source/io/camera.h"


void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(double _dt);

std::string loadShaderSrc(const char* filename);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

double dt = 0.0f;
double lastFrame = 0.0f;
double currentTime = 0.0f;

float x, y, z;
double dx, dy;
double scrollDX, scrollDY;

glm::mat4 transformationMatrix = glm::mat4(1.0f);

screen Screen;
camera camera::defaultCamera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
	int success;
	char infoLog[512];

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	
	std::cout << "Hello, endless space!" << std::endl;
	// glfw window creation
	
	if (!Screen.init()) {
		
		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Screen.setParameters();

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	shader Shader("../source/shaders/2Dcore.vs", "../source/shaders/2Dcore.fs");

	// render loop

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	while (!Screen.shouldClose()) {

		currentTime = glfwGetTime();
		dt = currentTime - lastFrame;
		lastFrame = currentTime;

		// input
		Screen.update();
		
		processInput(dt);

		// create transformations for the screen
		view = camera::defaultCamera.getViewMatrix();
		projection = glm::perspective(glm::radians(camera::defaultCamera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		Shader.activate();
		Shader.set3flt("viewPos", camera::defaultCamera.cameraPosition);

		// draw triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		Shader.setmat4("view", view);
		Shader.setmat4("projection", projection);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		
		Screen.newFrame();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly

void processInput(double _dt) {

	if(keyboard::key(GLFW_KEY_ESCAPE))
		Screen.setShouldClose(true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

std::string loadShaderSrc(const char* filename) {

	std::ifstream fromfile;
	std::stringstream buffer;

	std::string retval = "";

	fromfile.open(filename);

	if (fromfile.is_open()) {
		buffer << fromfile.rdbuf();

		retval = buffer.str();
	}
	else {
		std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << filename << std::endl;
	}

	fromfile.close();

	return retval;
}
