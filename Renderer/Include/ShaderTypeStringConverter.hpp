#pragma once

#include <glad/glad.h>

#include <string>

namespace Renderer {
class ShaderTypeStringConverter final {
public:
	ShaderTypeStringConverter() noexcept = delete;
	ShaderTypeStringConverter(const ShaderTypeStringConverter& other) noexcept = delete;
	ShaderTypeStringConverter(ShaderTypeStringConverter&& other) noexcept = delete;
	~ShaderTypeStringConverter() noexcept = delete;

public:
	ShaderTypeStringConverter& operator=(const ShaderTypeStringConverter& other) noexcept = delete;
	ShaderTypeStringConverter& operator=(ShaderTypeStringConverter&& other) noexcept = delete;

public:
	static const std::string getShaderTypeString(const GLenum shaderType);
};
}