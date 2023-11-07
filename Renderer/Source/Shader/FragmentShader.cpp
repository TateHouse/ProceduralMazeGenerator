#include "Shader/FragmentShader.hpp"

namespace Renderer::Shader {
FragmentShader::FragmentShader(const std::filesystem::path& path) noexcept: Shader {GL_FRAGMENT_SHADER, path} {

};
}
