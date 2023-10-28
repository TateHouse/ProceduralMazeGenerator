#pragma once

#include <memory>

#include "Utility/DeltaTimeManager.hpp"
#include "Utility/UnitScale.hpp"
#include "Utility/WindowManager.hpp"

namespace Renderer {
class Context {
public:
    Context() noexcept;
    virtual ~Context() noexcept = default;

public:
    void update() noexcept;

public:
    Utility::DeltaTimeManager* const getDeltaTimeManager() noexcept;
    Utility::WindowManager* const getWindowManager() noexcept;

private:
    std::unique_ptr<Utility::DeltaTimeManager> deltaTimeManager;
    std::unique_ptr<Utility::WindowManager> windowManager;
};
}