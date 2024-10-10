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

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

double dt = 0.0f;
double lastFrame = 0.0f;
double currentTime = 0.0f;

float x, y, z;
double dx, dy;
double scrollDX, scrollDY;

int parseSize = 1;
bool reloadTerrain = false;

glm::mat4 transformationMatrix = glm::mat4(1.0f);

screen Screen;
camera camera::defaultCamera(glm::vec3(4.0f, 4.0f, 4.0f));

float rotationAngle = 0.0f;
float rotationR = std::pow(2, 0.5) * camera::defaultCamera.cameraPosition.x;
float rotationX = camera::defaultCamera.cameraPosition.x;
float rotationZ = camera::defaultCamera.cameraPosition.z;

glm::vec3 test = glm::vec3(1.5f);
vCube VCube = vCube(material::emerald, test, glm::vec3(0.1f));

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

	shader Shader("/Users/ulysses/Desktop/source/projects/gaussianNoiseVisual/source/shaders/core.vs", "/Users/ulysses/Desktop/source/projects/gaussianNoiseVisual/source/shaders/nofade_core.fs");
	shader lightsourceShader("/Users/ulysses/Desktop/source/projects/gaussianNoiseVisual/source/shaders/core.vs", "/Users/ulysses/Desktop/source/projects/gaussianNoiseVisual/source/shaders/lightsource.fs");

	VCube.init();

	spotLight SpotLight = { 
		camera::defaultCamera.cameraPosition, camera::defaultCamera.cameraFront, 
		glm::cos(glm::radians(50.1f)), glm::cos(glm::radians(90.1f)), 
		1.0f, 0.07f, 0.032f, glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f)
	};

	// render loop

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
		
	//initialize gaussVector
	gaussDataSet gaussVector = gaussDataSet(parseSize * parseSize, 0.0f, 2.0f, 2.0f);

	//initialize positionsVector
	std::vector<glm::vec2> dots(gaussVector.size);
	
	//create initial terrain
	std::vector<terrain> VTerrain(gaussVector.size);
	for (int i = 0; i < gaussVector.size; ++i) {
		dots.push_back(glm::vec2(i / parseSize, i % parseSize));

		//VTerrain[i] = terrain(material::white_rubber, glm::vec3(dots.at(i).x, 1.0f, dots.at(i).y), glm::vec3 (1.0f), gaussVector.DataSet.at(i));
		VTerrain.push_back(terrain(material::white_rubber, glm::vec3(dots.at(i).x, -gaussVector.DataSet.at(i), dots.at(i).y), glm::vec3 (1.0f), gaussVector.DataSet.at(i)));

		VTerrain.at(i).init();
	}

	while (!Screen.shouldClose()) {
		reloadTerrain = false;

		currentTime = glfwGetTime();
		dt = currentTime - lastFrame;
		lastFrame = currentTime;

		// input
		Screen.update();
		
		processInput(dt);
		
		if (reloadTerrain) {
				//reloading terrain
				gaussVector.regen(parseSize * parseSize);

				//uncomment to see values
				//gaussVector.print();
				
				//clearing data
				VTerrain.clear();

				//clearing data
				dots.clear();


				for (int i = 0; i < gaussVector.size; ++i) {

					dots.push_back(glm::vec2(((i) / (parseSize)), ((i) % parseSize)));
					
					//uncomment to see values
					//std::cout << dots.at(i).x / parseSize << ' ' << dots.at(i).x << ' ' << dots.at(i).y / parseSize << ' ' << dots.at(i).y << std::endl;

					//VTerrain[i] = terrain(material::white_rubber, glm::vec3(dots.at(i).x, 1.0f, dots.at(i).y), glm::vec3 (1.0f), gaussVector.DataSet.at(i));
					VTerrain.push_back(terrain(material::white_rubber, glm::vec3((dots.at(i).x / parseSize), 0.0f, (dots.at(i).y / parseSize)), glm::vec3 (1.0f / (parseSize)), (gaussVector.DataSet.at(i))));

					VTerrain.at(i).init();
				}
				
				//finished reloading terrain with vectors the size of parseSize*parseSize and gaussVector.size elements
		}

		// create transformations for the screen
		view = camera::defaultCamera.getViewMatrix();
		projection = glm::perspective(glm::radians(camera::defaultCamera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		//camera::defaultCamera.yaw += 1;
		//std::cout << camera::defaultCamera.yaw << std::endl;
		//std::cout << camera::defaultCamera.pitch << std::endl;

		Shader.activate();
		Shader.set3flt("viewPos", camera::defaultCamera.cameraPosition);
		
		SpotLight.position = camera::defaultCamera.cameraPosition;
		SpotLight.direction = camera::defaultCamera.cameraFront;
		SpotLight.render(Shader);

		// draw triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		Shader.setmat4("view", view);
		Shader.setmat4("projection", projection);

		VCube.render(Shader);

		for (int i = 0; i < gaussVector.size; ++i) {
			VTerrain.at(i).render(Shader);
		}

		// glfw: swap buffers and poll IO events (KEYs pressed/released, mouse moved etc.)
		
		Screen.newFrame();

		//std::cout << camera::defaultCamera.cameraPosition.x << ' ' << camera::defaultCamera.cameraPosition.y << ' ' << camera::defaultCamera.cameraPosition.z << std::endl;
		
		if (rotationAngle != 360.0f)
			rotationAngle += 0.1f;
		else rotationAngle = 0.0f;

		//std::cout << rotationAngle << ' ' << ((int)camera::defaultCamera.yaw)%360 << std::endl;

		camera::defaultCamera.yaw = rotationAngle - 180.0f;
		camera::defaultCamera.updateCameraDirection(0.0f, 0.0f);

		rotationX = rotationR * glm::cos(glm::radians(rotationAngle));	
		rotationZ = rotationR * glm::sin(glm::radians(rotationAngle));

		camera::defaultCamera.cameraPosition.x = rotationX;
		camera::defaultCamera.cameraPosition.z = rotationZ;

		//std::cout << rotationX << ' ' << rotationZ << std::endl;
		
		//std::cout << std::asin(camera::defaultCamera.cameraPosition.y / (std::pow(2, 0.5) * camera::defaultCamera.cameraPosition.y));
		//std::cout << camera::defaultCamera.pitch << std::endl;

	}
	
	VCube.cleanUp();
	for (int i = 0; i < gaussVector.size; ++i) {
			VTerrain[i].cleanUp();
	}
	
	// glfw: terminate, clearing all previously allocated GLFW resources.

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant KEYs are pressed/released this frame and react accordingly

void processInput(double dt) {

	if(keyboard::key(GLFW_KEY_ESCAPE))
		Screen.setShouldClose(true);

	if (keyboard::key(GLFW_KEY_LEFT)) {
		
		std::cout << "LEFT arrow key pressed" << std::endl;			
	}

	if (keyboard::key(GLFW_KEY_RIGHT)) {
		
		std::cout << "RIGHT arrow key pressed" << std::endl;			
	}

	/*
	dx = mouse::getDX();
	dy = mouse::getDY();
	
	if (dx != 0 || dy != 0) {

		camera::defaultCamera.updateCameraDirection(dx, dy);
	}
	*/

	scrollDY = mouse::getScrollDY();

	if (scrollDY != 0) {

		camera::defaultCamera.updateCameraZoom(scrollDY);
	}

	if (keyboard::keyWentDn(GLFW_KEY_UP) && parseSize < 49) {
		parseSize++;
		reloadTerrain = true;
	}

	if (keyboard::keyWentDn(GLFW_KEY_DOWN) && parseSize > 1) {
		parseSize--;
		reloadTerrain = true;
	}
}
