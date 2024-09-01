#include "shader.h"

// main constructor
shader::shader() {}
shader::shader(const char* vertexShaderPath, const char* fragmentShaderPath) {

	generate(vertexShaderPath, fragmentShaderPath);
}

void shader::generate(const char* vertexShaderPath, const char* fragmentShaderPath) {

	int success;
	char infoLog[512];

	GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);

	// catch errors
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {

		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void shader::activate() {

	glUseProgram(shaderID);
}

std::string shader::loadShaderSrc(const char* filename) {

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

GLuint shader::compileShader(const char* filename, GLenum type) {

	int success;
	char infoLog[512];

	// create
	GLuint retval = glCreateShader(type);

	std::string shaderSrc = loadShaderSrc(filename);
	const GLchar* Shader = shaderSrc.c_str();
	glShaderSource(retval, 1, &Shader, nullptr);

	// compile
	glCompileShader(retval);

	// catch errors
	glGetShaderiv(retval, GL_COMPILE_STATUS, &success);
	if (!success) {

		glGetShaderInfoLog(retval, 512, nullptr, infoLog);
		std::cout << "ERR::SHADER::COMPILATION_FAILED@" << std::endl << filename << infoLog << std::endl;
	}

	return retval;
}

void shader::setbool(const std::string &name, bool value) {

	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}

void shader::set_int(const std::string &name, int value) {

	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void shader::set_flt(const std::string &name, float value) {

	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void shader::set3flt(const std::string &name, float value1, float value2, float value3) {

	glUniform3f(glGetUniformLocation(shaderID, name.c_str()), value1, value2, value3);
}

void shader::set3flt(const std::string& name, glm::vec3 value) {

	glUniform3f(glGetUniformLocation(shaderID, name.c_str()), value.x, value.y, value.z);
}

void shader::set4flt(const std::string &name, float value1, float value2, float value3, float value4) {

	glUniform4f(glGetUniformLocation(shaderID, name.c_str()), value1, value2, value3, value4);
}

void shader::set4flt(const std::string &name, glm::vec4 value) {

	glUniform4f(glGetUniformLocation(shaderID, name.c_str()), value.x, value.y, value.z, value.w);
}

void shader::setmat3(const std::string& name, glm::mat3 value) {

	glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void shader::setmat4(const std::string& name, glm::mat4 value) {

	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
