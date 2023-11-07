#pragma once

#include "Shader.hpp"

namespace Renderer::Shader {
class GeometryShader final : public Shader {
public:
    explicit GeometryShader(const std::filesystem::path& path) noexcept;
    GeometryShader(const GeometryShader&) = delete;
    GeometryShader(GeometryShader&&) noexcept = default;
    virtual ~GeometryShader() noexcept = default;

public:
    GeometryShader& operator=(const GeometryShader&) = delete;
    GeometryShader& operator=(GeometryShader&&) noexcept = default;
};
}