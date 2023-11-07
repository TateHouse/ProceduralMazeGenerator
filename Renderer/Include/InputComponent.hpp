#pragma once

#include "Context.hpp"
#include "Component.hpp"

namespace Renderer {
class InputComponent : public Component {
public:
    explicit InputComponent(Context& context) noexcept: Component {context} {

    }

    virtual ~InputComponent() noexcept = default;

public:
    virtual void initialize() = 0;
    virtual void postInitialize() = 0;
    virtual void update() = 0;
    virtual void postUpdate() = 0;
    virtual void render() = 0;
    virtual void postRender() = 0;
    virtual void destroy() = 0;

public:
    virtual void onKeyDown() = 0;
};
}