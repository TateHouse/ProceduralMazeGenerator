#pragma once

#include <string>
#include <unordered_map>

namespace Renderer {
class OrthographicCamera;
}

namespace Renderer::Utility {
class CameraManager final {
public:
    void addCamera(const std::string& name, Renderer::OrthographicCamera* camera);
    void removeCamera(const std::string& name);
    [[nodiscard]] Renderer::OrthographicCamera* getCamera(const std::string& name) const;

private:
    std::unordered_map<std::string, Renderer::OrthographicCamera*> cameras {};
};
}