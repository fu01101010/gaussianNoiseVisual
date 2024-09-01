#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class shader {

public:
	unsigned int shaderID;

	// main constructor
	shader();
	shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void generate(const char* vertexShaderPath, const char* fragmentShaderPath);

	void activate();

	// utility funcs
	std::string loadShaderSrc(const char* filepath);
	GLuint compileShader(const char* filepath, GLenum type);

	// uniform funcs
	void setbool(const std::string& name, bool value);
	void set_int(const std::string& name, int value);
	void set_flt(const std::string& name, float value);
	void set3flt(const std::string& name, float value1, float value2, float value3);
	void set3flt(const std::string& name, glm::vec3 value);
	void set4flt(const std::string& name, float value1, float value2, float value3, float value4);
	void set4flt(const std::string& name, glm::vec4 value);
	void setmat3(const std::string& name, glm::mat3 value);
	void setmat4(const std::string& name, glm::mat4 value);
};

#endif
