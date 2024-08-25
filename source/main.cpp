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

#include "io/mouse.h"
#include "io/keyboard.h"


void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

std::string loadShaderSrc(const char* filename);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	int success;
	char infoLog[512];

	//glm test here
	//glm::vec3 vec(1.0f, 2.0f, 3.0f);
	//std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;

	// glfw: initialize and configure

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	std::cout << "Hello, endless space!" << std::endl;
	// glfw window creation

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "gaussN", NULL, NULL);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// glad: load all OpenGL function pointers

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

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

	while (!glfwWindowShouldClose(window)) {
		// input
		
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// use shader program
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		// draw triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		processInput(window);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly

void processInput(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
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
