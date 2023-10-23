#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <filesystem>

namespace Renderer {
class Shader final {
public:
	Shader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath);
	Shader(const Shader& other) = delete;
	Shader(Shader&& other) noexcept = default;
	~Shader() noexcept;

public:
	Shader& operator=(const Shader& other) = delete;
	Shader& operator=(Shader&& other) noexcept = default;

public:
	void use() const noexcept;
	void setMat4x4(const std::string_view uniformName,
	               const glm::mat4& matrix,
	               const bool transpose = false) const noexcept;

private:
	static GLuint createShader(const std::filesystem::path& shaderPath, const GLenum shaderType);

private:
	static constexpr std::size_t INFO_LOG_SIZE {512};
	GLuint shaderProgram;
};
}