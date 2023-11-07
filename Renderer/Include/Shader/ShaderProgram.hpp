#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <unordered_map>

#include "FragmentShader.hpp"
#include "Shader.hpp"
#include "VertexShader.hpp"

namespace Renderer::Shader {
class ShaderProgram final {
public:
    ShaderProgram(VertexShader&& vertexShader, FragmentShader&& fragmentShader);
    ShaderProgram(const ShaderProgram& other) = delete;
    ShaderProgram(ShaderProgram&& other) noexcept = default;
    ~ShaderProgram() noexcept;

public:
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram& operator=(ShaderProgram&&) noexcept = default;

public:
    void attachShader(Shader&& shader);
    void detachShader(GLenum shaderType);
    void link() const;
    void reload();
    void use() const;
    void setUniform1f(const std::string_view name, const float x) const;
    void setUniform3fv(const std::string_view name, const glm::vec3& vector) const;
    void setUniformMatrix4x4fv(const std::string_view name,
                               const glm::mat4& matrix,
                               const bool transpose = false) const;

private:
    GLuint getUniformLocation(const std::string_view name) const;

private:
    GLuint id {glCreateProgram()};
    std::unordered_map<GLenum, Shader> shaders;
};
}