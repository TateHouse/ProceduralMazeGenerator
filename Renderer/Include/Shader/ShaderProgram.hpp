#pragma once

#include <glad/glad.h>

#include <unordered_map>

#include "Shader.hpp"

namespace Renderer::Shader {
class ShaderProgram final {
public:
    ShaderProgram() noexcept = default;
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

private:
    GLuint id {glCreateProgram()};
    std::unordered_map<GLenum, Shader> shaders;
};
}