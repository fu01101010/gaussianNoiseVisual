#ifndef TERRAINGEN_HPP
#define TERRAINGEN_HPP

#include "../vModel.h"
#include "../material.h"

class terrain : public vModel {

public:

	glm::vec3 position;
	glm::vec3 size;

	material Material;

	vCube() {}
	vCube(material Material, glm::vec3 position, glm::vec3 size) 
		: Material(Material), position(position), size(size) {}

	void init() {

		unsigned int nVertices = 3;

		float vertices[] = {
			//position		normal			aColor
			-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f, 1.0f
		};

		std::vector<unsigned int> indices(nVertices);

		for (int i = 0; i < nVertices; ++i) {

			indices[i] = i;
		}

		meshes.push_back(vMesh(vertex::genList(vertices, nVertices), indices));
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
