#pragma once

#include <memory>

#include "Utility/DeltaTimeManager.hpp"
#include "Utility/UnitScale.hpp"

namespace Renderer {
class Context {
public:
    Context() noexcept;
    virtual ~Context() noexcept = default;

public:
    void update() noexcept;

public:
    Utility::DeltaTimeManager* const getDeltaTimeManager() noexcept;

private:
    std::unique_ptr<Utility::DeltaTimeManager> deltaTimeManager;
};
}