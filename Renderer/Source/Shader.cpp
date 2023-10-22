#include "Shader.hpp"

#include <array>
#include <filesystem>

#include "Utility/FileLoader.hpp"
#include "ShaderCompilationException.hpp"
#include "ShaderLinkingException.hpp"

namespace Renderer {
Shader::Shader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath) {
	GLuint vertexShader {0};
	GLuint fragmentShader {0};
	
	try {
		vertexShader = Shader::createShader(vertexShaderPath, GL_VERTEX_SHADER);
		fragmentShader = Shader::createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
		
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		
		auto success {0};
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			auto infoLog {std::array<char, INFO_LOG_SIZE> {}};
			glGetProgramInfoLog(shaderProgram, INFO_LOG_SIZE, nullptr, infoLog.data());
			
			throw ShaderLinkingException {vertexShaderPath, fragmentShaderPath, infoLog.data()};
		}
		
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	} catch (...) {
		if (vertexShader != 0) {
			glDeleteShader(vertexShader);
		}
		
		if (fragmentShader != 0) {
			glDeleteShader(fragmentShader);
		}
		
		throw;
	}
}

Shader::~Shader() noexcept {
	glDeleteProgram(shaderProgram);
}

void Shader::use() const noexcept {
	glUseProgram(shaderProgram);
}

GLuint Shader::createShader(const std::filesystem::path& shaderPath, const GLenum shaderType) {
	try {
		auto fileLoader {Utility::FileLoader {shaderPath}};
		
		const auto shaderSource {fileLoader.load()};
		const auto* shaderSourcePointer {shaderSource.c_str()};
		
		auto shader {glCreateShader(shaderType)};
		glShaderSource(shader, 1, &shaderSourcePointer, nullptr);
		glCompileShader(shader);
		
		auto success {0};
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			auto infoLog {std::array<char, INFO_LOG_SIZE> {}};
			glGetShaderInfoLog(shader, INFO_LOG_SIZE, nullptr, infoLog.data());
			
			throw ShaderCompilationException {shaderType, shaderPath, infoLog.data()};
		}
		
		return shader;
	} catch (const std::filesystem::filesystem_error& exception) {
		throw ShaderCompilationException {shaderType, shaderPath, exception.what()};
	}
}
}