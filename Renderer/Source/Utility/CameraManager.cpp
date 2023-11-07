#include "Utility/CameraManager.hpp"

#include <stdexcept>

namespace Renderer::Utility {
void CameraManager::addCamera(const std::string& name, Renderer::OrthographicCamera* camera) {
    if (camera == nullptr) {
        throw std::invalid_argument {"The camera cannot be null."};
    }

    if (name.empty()) {
        throw std::invalid_argument {"The name cannot be empty."};
    }

    cameras.try_emplace(name, camera);
}

void CameraManager::removeCamera(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument {"The name cannot be empty."};
    }

    cameras.erase(name);
}

Renderer::OrthographicCamera* CameraManager::getCamera(const std::string& name) const {
    if (name.empty()) {
        throw std::invalid_argument {"The name cannot be empty."};
    }

    const auto camera {cameras.find(name)};
    if (camera == cameras.end()) {
        return nullptr;
    }

    return camera->second;
}
}