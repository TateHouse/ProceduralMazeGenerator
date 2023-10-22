#include "ShaderLinkingException.hpp"

#include <format>

namespace Renderer {
ShaderLinkingException::ShaderLinkingException(const std::filesystem::path& vertexShaderPath,
                                               const std::filesystem::path& fragmentShaderPath,
                                               const std::string& message) :
		std::runtime_error {message},
		message {std::format(
				"Type: Shader Program Linking\nVertex Shader Path: {}\nFragment Shader Path: {}\nMessage: {}",
				vertexShaderPath.string(),
				fragmentShaderPath.string(),
				message)} {
	
}

const char* ShaderLinkingException::what() const noexcept {
	return message.c_str();
}
}