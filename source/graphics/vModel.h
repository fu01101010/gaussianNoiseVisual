#ifndef VMODEL_H
#define VMODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "vMesh.h"

class vModel {

public:

	std::vector<vMesh> meshes;

	vModel();

	void init();

	void render(shader Shader);

	void cleanUp();
};

#endif
