#ifndef TERRAINGEN_HPP
#define TERRAINGEN_HPP

#include "../vModel.h"
#include "../material.h"

struct item {

	float coords[9] = {};
	float normal[3] = {};
	float aColor[3] = {};
};

class terrain : public vModel {

public:

	glm::vec3 position;
	glm::vec3 size;

	float height;

	material Material;

	terrain() {}
	terrain(material Material, glm::vec3 position, glm::vec3 size, float height) 
		: Material(Material), position(position), size(size), height(height) {}

	void init() {

		unsigned int nItems = 36;
		std::vector<item> terrainData;

		float vertices[] = {
			//position		 normal			aColor
			-0.5f, 0.0f,   -0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			-0.5f, 0.0f,    0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, 0.0f,    0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,

			-0.5f, 0.0f,   -0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, 0.0f,    0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, 0.0f,   -0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,

			-0.5f, height, -0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			-0.5f, height,  0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, height,  0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,

			-0.5f, height, -0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, height,  0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, height, -0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,

			-0.5f, 0.0f,   -0.5f,	-1.0f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			-0.5f, 0.0f,    0.5f,	-1.0f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			-0.5f, height, -0.5f,	-1.0f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f,

			-0.5f, height, -0.5f,	-1.0f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			-0.5f, height,  0.5f,	-1.0f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			-0.5f, 0.0f,    0.5f,	-1.0f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f,

			-0.5f, 0.0f,   -0.5f,	 0.0f, -1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, 0.0f,   -0.5f,	 0.0f, -1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, height, -0.5f,	 0.0f, -1.0f, 0.0f,	0.0f, 0.0f, 0.0f,

			-0.5f, height, -0.5f,	 0.0f, -1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, height, -0.5f,	 0.0f, -1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			-0.5f, 0.0f,   -0.5f,	 0.0f, -1.0f, 0.0f,	0.0f, 0.0f, 0.0f,

			 0.5f, 0.0f,   -0.5f,	 0.0f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, 0.0f,    0.5f,	 0.0f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, height, -0.5f,	 0.0f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f,

			 0.5f, height, -0.5f,	 0.0f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, height,  0.5f,	 0.0f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, 0.0f,    0.5f,	 0.0f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f,

			 0.5f, 0.0f,    0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			-0.5f, 0.0f,    0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			 0.5f, height,  0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,

			 0.5f, height,  0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			-0.5f, height,  0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
			-0.5f, 0.0f,    0.5f,	 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f,



		};

		std::vector<unsigned int> indices(nItems);

		for (int i = 0; i < nItems; ++i) {

			indices[i] = i;
		}

		meshes.push_back(vMesh(vertex::genList(vertices, nItems), indices));
	}

	void render(shader Shader) {

		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, position);
		model = glm::scale(model, size);
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-45.0f), glm::vec3(0.5f));

		Shader.setmat4("model", model);
		Shader.set3flt("Material.ambient", Material.ambient);
		Shader.set3flt("Material.diffuse", Material.diffuse);
		Shader.set3flt("Material.specular", Material.specular);
		Shader.set_flt("Material.reflectivity", Material.reflectivity);
		
		vModel::render(Shader);
	}

};

#endif
