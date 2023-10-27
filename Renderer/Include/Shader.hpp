#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <optional>
#include <filesystem>

namespace Renderer {
class Shader final {
public:
    Shader(const std::filesystem::path& vertexShaderPath,
           const std::filesystem::path& fragmentShaderPath,
           std::optional<std::filesystem::path> geometryShaderPath = std::nullopt);
	Shader(const Shader& other) = delete;
	Shader(Shader&& other) noexcept = default;
	~Shader() noexcept;

public:
	Shader& operator=(const Shader& other) = delete;
	Shader& operator=(Shader&& other) noexcept = default;

public:
	void use() const noexcept;
    void setUniform1f(const std::string_view uniformName, const float value) const noexcept;
    void setUniform3fv(const std::string_view uniformName, const glm::vec3& vector) const noexcept;
    void setUniformMatrix4x4fv(const std::string_view uniformName,
                               const glm::mat4& matrix,
                               const bool transpose = false) const noexcept;

private:
	static GLuint createShader(const std::filesystem::path& shaderPath, const GLenum shaderType);

private:
	static constexpr std::size_t INFO_LOG_SIZE {512};
	GLuint shaderProgram;
};
}