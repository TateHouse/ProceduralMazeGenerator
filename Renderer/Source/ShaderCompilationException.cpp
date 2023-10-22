#include "ShaderCompilationException.hpp"

#include <format>

#include "ShaderTypeStringConverter.hpp"

namespace Renderer {
ShaderCompilationException::ShaderCompilationException(const GLenum shaderType,
                                                       const std::filesystem::path& shaderPath,
                                                       const std::string& message) :
		std::runtime_error {message},
		message {std::format("Type: {}\nPath: {}\nMessage: {}",
		                     ShaderTypeStringConverter::getShaderTypeString(shaderType),
		                     shaderPath.string(),
		                     message)} {
	
}

const char* ShaderCompilationException::what() const noexcept {
	return message.c_str();
}
}