#include <shader.h>
#include <iostream>
#include <fstream>
#include <gtc/type_ptr.hpp>

Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource) {
	load(vertexSource, fragmentSource);
}

Shader::Shader(const Path& vertexPath, const Path& fragmentPath) {
	// load sources from files
	std::string vertexSource, fragmentSource;

// Loads Shader
	load(vertexSource, fragmentSource);
}

void Shader::Bind() {
	// Call pyramid shader
	glUseProgram(_shaderProgram);
}

void Shader::load(const std::string &vertexSource, const std::string &fragmentSource) {
	const char* vShaderCode = vertexSource.c_str();
	const char* fShaderCode = fragmentSource.c_str();

		auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::FAILED\n" << infoLog << std::endl;
	}

	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
	glCompileShader(fragmentShader);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::FAILED\n" << infoLog << std::endl;
	}

	// Link Shader to Fragments
	_shaderProgram = glCreateProgram();

	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	glLinkProgram(_shaderProgram);

	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::LINK_FAILED\n" << infoLog << std::endl;
	}

	// Stores links and deletes temporary objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLint Shader::getUniformLocation(const std::string &uniformName) {

	return glGetUniformLocation(_shaderProgram, uniformName.c_str());
}

void Shader::SetMat4(const std::string& uniformName, const glm::mat4& mat4) {
	auto uniformLoc = getUniformLocation(uniformName);
	
	if (uniformLoc != -1) {	
		Bind();
		// Update uniform value with matrix 4 for low values
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat4));
	}
}
