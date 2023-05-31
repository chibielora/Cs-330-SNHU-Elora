#pragma once
#include <filesystem>
#include <string>
#include <GLAD/glad.h>
#include <glm.hpp>

using Path = std::filesystem::path;

class Shader {
public:
	Shader() = default;
	Shader(const std::string& vertexSource, const std::string& fragmentSource);
	Shader(const Path& vertexPath, const Path& fragmentPath);

	void Bind();

	void SetMat4(const std::string& uniformName, const glm::mat4& mat4);

private:
	void load(const std::string& vertexSource, const std::string& fragmentSource);
	GLint getUniformLocation(const std::string& uniformName);

private:
	GLuint _shaderProgram;
};

