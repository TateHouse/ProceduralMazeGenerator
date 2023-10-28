#pragma once

#include "Shader.hpp"

namespace Renderer::Shader {
class VertexShader final : public Shader {
public:
    explicit VertexShader(const std::filesystem::path& path) noexcept;
    VertexShader(const VertexShader&) = delete;
    VertexShader(VertexShader&&) noexcept = default;
    virtual ~VertexShader() noexcept = default;

public:
    VertexShader& operator=(const VertexShader&) = delete;
    VertexShader& operator=(VertexShader&&) noexcept = default;
};
}