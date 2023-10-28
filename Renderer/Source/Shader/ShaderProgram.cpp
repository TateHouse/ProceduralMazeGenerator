#include "Shader/ShaderProgram.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <stdexcept>

namespace Renderer::Shader {
ShaderProgram::ShaderProgram(Renderer::Shader::VertexShader&& vertexShader,
                             Renderer::Shader::FragmentShader&& fragmentShader) {
    attachShader(std::move(vertexShader));
    attachShader(std::move(fragmentShader));
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id);
}

void ShaderProgram::attachShader(Shader&& shader) {
    const auto shaderType {shader.getType()};

    if (auto iterator {shaders.find(shaderType)}; iterator != shaders.end()) {
        glDetachShader(id, iterator->second.getId());
        shaders.erase(iterator);
    }

    glAttachShader(id, shader.getId());
    shaders.try_emplace(shaderType, std::move(shader));
}

void ShaderProgram::detachShader(GLenum shaderType) {
    auto iterator {shaders.find(shaderType)};
    if (iterator != shaders.end()) {
        glDetachShader(id, iterator->second.getId());
        shaders.erase(iterator);
    }
}

void ShaderProgram::link() const {
    glLinkProgram(id);

    GLint isLinked {0};
    glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        static constexpr auto infoLogSize {512};
        auto infoLog {std::array<char, infoLogSize> {}};
        glGetProgramInfoLog(id, infoLogSize, nullptr, infoLog.data());
        glDeleteProgram(id);

        const auto message {std::format("Failed to link shader program: {}", infoLog.data())};
        throw std::runtime_error {message};
    }
}

void ShaderProgram::reload() {
    for (auto& [shaderType, shader] : shaders) {
        detachShader(shaderType);
        shader.reload();
        attachShader(std::move(shader));
    }

    link();
}

void ShaderProgram::use() const {
    if (id == 0) {
        throw std::runtime_error {"Shader program is not linked."};
    }

    glUseProgram(id);
}

void ShaderProgram::setUniform1f(const std::string_view name, const float x) const {
    glUniform1f(getUniformLocation(name), x);
}

void ShaderProgram::setUniform3fv(const std::string_view name, const glm::vec3& vector) const {
    glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(vector));
}

void ShaderProgram::setUniformMatrix4x4fv(const std::string_view name,
                                          const glm::mat4& matrix,
                                          const bool transpose) const {
    glUniformMatrix4fv(getUniformLocation(name), 1, transpose, glm::value_ptr(matrix));
}

GLuint ShaderProgram::getUniformLocation(const std::string_view name) const {
    return glGetUniformLocation(id, name.data());
}
}