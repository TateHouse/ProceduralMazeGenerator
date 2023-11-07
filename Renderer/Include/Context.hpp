#pragma once

#include <memory>

#include "Utility/CameraManager.hpp"
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
    [[nodiscard]] const bool getIsRunning() const noexcept;
    void stopRunning() noexcept;
    Utility::CameraManager* const getCameraManager() noexcept;
    Utility::DeltaTimeManager* const getDeltaTimeManager() noexcept;
    Utility::WindowManager* const getWindowManager() noexcept;

private:
    bool isRunning {true};
    std::unique_ptr<Utility::CameraManager> cameraManager;
    std::unique_ptr<Utility::DeltaTimeManager> deltaTimeManager;
    std::unique_ptr<Utility::WindowManager> windowManager;
};
}