#include "light.h"

void pointLight::render(shader Shader, int IDx) {

	std::string name = "PointLights[" + std::to_string(IDx) + "]";

	Shader.set3flt(name + ".position", position);

	Shader.set_flt(name + ".k0", k0);
	Shader.set_flt(name + ".k1", k1);
	Shader.set_flt(name + ".k2", k2);

	Shader.set3flt(name + ".ambient", ambient);
	Shader.set3flt(name + ".diffuse", diffuse);
	Shader.set3flt(name + ".specular", specular);
}

void directLight::render(shader Shader) {

	std::string name = "DirectLight";

	Shader.set3flt(name + ".direction", direction);

	Shader.set3flt(name + ".ambient", ambient);
	Shader.set3flt(name + ".diffuse", diffuse);
	Shader.set3flt(name + ".specular", specular);
}


void spotLight::render(shader Shader) {

	std::string name = "SpotLight";

	Shader.set3flt(name + ".position", position);
	Shader.set3flt(name + ".direction", direction);
	
	Shader.set_flt(name + ".cutOff", cutOff);
	Shader.set_flt(name + ".outerCutOff", outerCutOff);

	Shader.set_flt(name + ".k0", k0);
	Shader.set_flt(name + ".k1", k1);
	Shader.set_flt(name + ".k2", k2);

	Shader.set3flt(name + ".ambient", ambient);
	Shader.set3flt(name + ".diffuse", diffuse);
	Shader.set3flt(name + ".specular", specular);
}
