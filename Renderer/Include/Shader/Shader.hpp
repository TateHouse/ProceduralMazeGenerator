#pragma once

#include "glad/glad.h"

#include <filesystem>

namespace Renderer::Shader {
class Shader {
public:
    Shader(const GLenum type, const std::filesystem::path& path) noexcept;
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) noexcept = default;
    virtual ~Shader() noexcept;

public:
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&&) noexcept = default;

public:
    void reload() noexcept;
    [[nodiscard]] const GLuint getType() const noexcept;
    [[nodiscard]] GLuint getId() const noexcept;

private:
    void compile();

private:
    std::filesystem::path path;
    GLenum type;
    GLuint id;
};
}