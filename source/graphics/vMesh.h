#ifndef VMESH_H
#define VMESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <vector>

#include "shader.h"

struct vertex {

	glm::vec3 position;
	glm::vec3 normal;	
	glm::vec3 aColor;

	static std::vector<struct vertex> genList(float* vertices, int nVertices);
};

typedef struct vertex vertex;

class vMesh {

public:

	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO;

	vMesh();
	vMesh(std::vector<vertex> vertices, std::vector<unsigned int> indicess);

	void render(shader Shader);

	void cleanUp();
	
private:

	unsigned int VBO, EBO;
	
	void setUp();
};

#endif
