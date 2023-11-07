#include "Utility/WindowManager.hpp"

#include <stdexcept>

namespace Renderer::Utility {
void WindowManager::addWindow(const std::string& name, Renderer::Window* window) {
    if (window == nullptr) {
        throw std::invalid_argument {"The window cannot be null."};
    }

    if (name.empty()) {
        throw std::invalid_argument {"The name cannot be empty."};
    }

    windows.try_emplace(name, window);
}

void WindowManager::removeWindow(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument {"The name cannot be empty."};
    }

    windows.erase(name);
}

Renderer::Window* WindowManager::getWindow(const std::string& name) const {
    if (name.empty()) {
        throw std::invalid_argument {"The name cannot be empty."};
    }

    const auto window {windows.find(name)};
    if (window == windows.end()) {
        return nullptr;
    }

    return window->second;
}
}