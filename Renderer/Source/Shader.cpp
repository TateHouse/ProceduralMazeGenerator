#include "Shader.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <filesystem>

#include "Utility/FileLoader.hpp"
#include "ShaderCompilationException.hpp"
#include "ShaderLinkingException.hpp"

namespace Renderer {
Shader::Shader(const std::filesystem::path& vertexShaderPath,
               const std::filesystem::path& fragmentShaderPath,
               std::optional<std::filesystem::path> geometryShaderPath) {
    GLuint vertexShader {0};
    GLuint fragmentShader {0};
    GLuint geometryShader {0};

    try {
        vertexShader = Shader::createShader(vertexShaderPath, GL_VERTEX_SHADER);
        fragmentShader = Shader::createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        if (geometryShaderPath.has_value()) {
            geometryShader = Shader::createShader(geometryShaderPath.value(), GL_GEOMETRY_SHADER);
            glAttachShader(shaderProgram, geometryShader);
        }

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
        glDeleteShader(geometryShader);
    } catch (...) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteShader(geometryShader);
        throw;
    }
}

Shader::~Shader() noexcept {
    glDeleteProgram(shaderProgram);
}

void Shader::use() const noexcept {
    glUseProgram(shaderProgram);
}

void Shader::setUniform1f(const std::string_view uniformName, const float value) const noexcept {
    const auto uniformLocation {glGetUniformLocation(shaderProgram, uniformName.data())};
    glUniform1f(uniformLocation, value);
}

void Shader::setUniform3fv(const std::string_view uniformName, const glm::vec3& vector) const noexcept {
    const auto uniformLocation {glGetUniformLocation(shaderProgram, uniformName.data())};
    glUniform3fv(uniformLocation, 1, glm::value_ptr(vector));
}

void Shader::setUniformMatrix4x4fv(const std::string_view uniformName,
                                   const glm::mat4& matrix,
                                   const bool transpose) const noexcept {
    const auto uniformLocation {glGetUniformLocation(shaderProgram, uniformName.data())};
    glUniformMatrix4fv(uniformLocation, 1, transpose, glm::value_ptr(matrix));
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