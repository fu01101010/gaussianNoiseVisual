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
#include "../source/graphics/material.h"

#include "../source/graphics/vMesh.h"
#include "../source/graphics/vModel.h"
#include "../source/graphics/models/vCube.hpp"
#include "../source/graphics/models/vLightSource.hpp"
#include "../source/graphics/models/vTerrainGen.hpp"

#include "../source/io/mouse.h"
#include "../source/io/keyboard.h"
#include "../source/io/screen.h"
#include "../source/io/camera.h"

#include "../source/math/gauss.h"


void processInput(double dt);

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

	shader Shader("/Users/ulysses/Desktop/source/projects/gaussianNoiseVisual/source/shaders/core.vs", "/Users/ulysses/Desktop/source/projects/gaussianNoiseVisual/source/shaders/core.fs");
	shader lightsourceShader("/Users/ulysses/Desktop/source/projects/gaussianNoiseVisual/source/shaders/core.vs", "/Users/ulysses/Desktop/source/projects/gaussianNoiseVisual/source/shaders/lightsource.fs");

	vCube VCube = vCube(material::black_rubber, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f));
	VCube.init();

	terrain VTerrain = terrain(material::white_rubber, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 (1.1f));
	VTerrain.init();

	spotLight SpotLight = { 
		camera::defaultCamera.cameraPosition, camera::defaultCamera.cameraFront, 
		glm::cos(glm::radians(12.1f)), glm::cos(glm::radians(20.1f)), 
		1.0f, 0.07f, 0.032f, glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f)
	};

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
		
		SpotLight.position = camera::defaultCamera.cameraPosition;
		SpotLight.direction = camera::defaultCamera.cameraFront;
		SpotLight.render(Shader);
		

		// draw triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		Shader.setmat4("view", view);
		Shader.setmat4("projection", projection);

		//VCube.render(Shader);
		VTerrain.render(Shader);

		// glfw: swap buffers and poll IO events (KEYs pressed/released, mouse moved etc.)
		
		Screen.newFrame();
	}
	
	//VCube.cleanUp();
	VTerrain.cleanUp();

	// glfw: terminate, clearing all previously allocated GLFW resources.

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant KEYs are pressed/released this frame and react accordingly

void processInput(double dt) {

	if(keyboard::key(GLFW_KEY_ESCAPE))
		Screen.setShouldClose(true);

	if (keyboard::key(GLFW_KEY_E)) {

		camera::defaultCamera.updateCameraPosition(cameraDirection::FORWARD, dt);
	}

	if (keyboard::key(GLFW_KEY_S)) {

		camera::defaultCamera.updateCameraPosition(cameraDirection::LEFT, dt);
	}

	if (keyboard::key(GLFW_KEY_D)) {

		camera::defaultCamera.updateCameraPosition(cameraDirection::BACKWARD, dt);
	}

	if (keyboard::key(GLFW_KEY_F)) {

		camera::defaultCamera.updateCameraPosition(cameraDirection::RIGHT, dt);
	}

	if (keyboard::key(GLFW_KEY_SPACE)) {

		camera::defaultCamera.updateCameraPosition(cameraDirection::UP, dt);
	}

	if (keyboard::key(GLFW_KEY_LEFT_SHIFT)) {

		camera::defaultCamera.updateCameraPosition(cameraDirection::DOWN, dt);
	}

	dx = mouse::getDX();
	dy = mouse::getDY();

	if (dx != 0 || dy != 0) {

		camera::defaultCamera.updateCameraDirection(dx, dy);
	}

	scrollDY = mouse::getScrollDY();

	if (scrollDY != 0) {

		camera::defaultCamera.updateCameraZoom(scrollDY);
	}

}
