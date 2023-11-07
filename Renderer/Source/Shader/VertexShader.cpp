#include "Shader/VertexShader.hpp"

namespace Renderer::Shader {
VertexShader::VertexShader(const std::filesystem::path& path) noexcept: Shader {GL_VERTEX_SHADER, path} {

};
}