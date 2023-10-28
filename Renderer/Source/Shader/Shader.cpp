#include "Shader/Shader.hpp"

#include <array>
#include <format>

#include "Utility/FileLoader.hpp"

namespace Renderer::Shader {
Shader::Shader(const GLenum type, const std::filesystem::path& path) noexcept: path {path}, type {type} {
    compile();
}

Shader::~Shader() noexcept {
    glDeleteShader(id);
}

void Shader::reload() noexcept {
    glDeleteShader(id);
    compile();
}

const GLuint Shader::getType() const noexcept {
    return type;
}

GLuint Shader::getId() const noexcept {
    return id;
}

void Shader::compile() {
    auto fileLoader {Renderer::Utility::FileLoader {path}};
    const auto fileSource {fileLoader.load()};
    const auto* const fileSourcePointer {fileSource.c_str()};

    id = glCreateShader(type);
    glShaderSource(id, 1, &fileSourcePointer, nullptr);
    glCompileShader(id);

    auto compilationStatus {0};
    glGetShaderiv(id, GL_COMPILE_STATUS, &compilationStatus);
    if (compilationStatus == GL_FALSE) {
        static constexpr auto infoLogSize {512};
        auto infoLog {std::array<char, infoLogSize> {}};
        glGetShaderInfoLog(id, infoLogSize, nullptr, infoLog.data());

        // TODO: Throw custom exception.
        const auto message {std::format("Failed to compile shader: {}", infoLog.data())};
        throw std::runtime_error {message};
    }
}
}