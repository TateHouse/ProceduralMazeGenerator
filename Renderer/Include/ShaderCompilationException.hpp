#pragma once

#include <glad/glad.h>

#include <filesystem>
#include <stdexcept>

namespace Renderer {
class ShaderCompilationException final : public std::runtime_error {
public:
	ShaderCompilationException(const GLenum shaderType,
	                           const std::filesystem::path& shaderPath,
	                           const std::string& message);
	ShaderCompilationException(const ShaderCompilationException& other) = default;
	ShaderCompilationException(ShaderCompilationException&& other) noexcept = default;
	~ShaderCompilationException() noexcept = default;

public:
	ShaderCompilationException& operator=(const ShaderCompilationException& other) = delete;
	ShaderCompilationException& operator=(ShaderCompilationException&& other) noexcept = delete;

public:
	const char* what() const noexcept override;

private:
	const std::string message;
};
}