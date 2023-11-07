#include "Shader/GeometryShader.hpp"

namespace Renderer::Shader {
GeometryShader::GeometryShader(const std::filesystem::path& path) noexcept: Shader {GL_GEOMETRY_SHADER, path} {

}
}