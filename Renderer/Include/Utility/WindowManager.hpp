#pragma once

#include <string>
#include <unordered_map>

namespace Renderer {
class Window;
}
namespace Renderer::Utility {
// TODO: Refactor to use a component manager base class.
class WindowManager final {
public:
    void addWindow(const std::string& name, Renderer::Window* window);
    void removeWindow(const std::string& name);
    [[nodiscard]] Renderer::Window* getWindow(const std::string& name) const;

private:
    std::unordered_map<std::string, Renderer::Window*> windows {};
};
}