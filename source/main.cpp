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

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	// process vertex data via GPU
	
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexShaderSrc = loadShaderSrc("../source/shaders/vertex_core.glsl");

	const char* vertexShaderSrcCSTR = vertexShaderSrc.c_str();

	glShaderSource(vertexShader, 1, &vertexShaderSrcCSTR, nullptr);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {

		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}

	// process fragment data
	
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentShaderSrc = loadShaderSrc("../source/shaders/fragment_core.glsl");

	const char* fragmentShaderSrcCSTR = fragmentShaderSrc.c_str();

	glShaderSource(fragmentShader, 1, &fragmentShaderSrcCSTR, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {

		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}
	
	// shader programs

	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// interpret vertex data via GPU

	glBindVertexArray(VAO);

	// put vertices in buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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

		
		

		// use shader program
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		// draw triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

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
