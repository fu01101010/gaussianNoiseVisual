#include "vModel.h"

vModel::vModel() {}

void vModel::init() {}

void vModel::render(shader Shader) {

	for (vMesh mesh : meshes) {

		mesh.render(Shader);
	}
}

void vModel::cleanUp() {

	for (vMesh mesh : meshes) {

		mesh.cleanUp();
	}
}
