#pragma once

#include <glad/glad.h>

#include <filesystem>
#include <stdexcept>

namespace Renderer {
class ShaderLinkingException final : public std::runtime_error {
public:
	ShaderLinkingException(const std::filesystem::path& vertexShaderPath,
	                       const std::filesystem::path& fragmentShaderPath,
	                       const std::string& message);
	ShaderLinkingException(const ShaderLinkingException& other) = default;
	ShaderLinkingException(ShaderLinkingException&& other) noexcept = default;
	~ShaderLinkingException() noexcept = default;

public:
	ShaderLinkingException& operator=(const ShaderLinkingException& other) = delete;
	ShaderLinkingException& operator=(ShaderLinkingException&& other) noexcept = delete;

public:
	const char* what() const noexcept override;

private:
	const std::string message;
};
}