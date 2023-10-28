#pragma once

#include "Shader.hpp"

namespace Renderer::Shader {
class FragmentShader final : public Shader {
public:
    explicit FragmentShader(const std::filesystem::path& path) noexcept;
    FragmentShader(const FragmentShader&) = delete;
    FragmentShader(FragmentShader&&) noexcept = delete;
    virtual ~FragmentShader() noexcept = default;

public:
    FragmentShader& operator=(const FragmentShader&) = delete;
    FragmentShader& operator=(FragmentShader&&) noexcept = delete;
};
}