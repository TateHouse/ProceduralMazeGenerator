#pragma once

#include "Context.hpp"

namespace Renderer {
class Component {
public:
    explicit Component(Context& context) noexcept: context {context} {

    }

    virtual ~Component() noexcept = default;

public:
    virtual void initialize() = 0;
    virtual void postInitialize() = 0;
    virtual void update() = 0;
    virtual void postUpdate() = 0;
    virtual void render() = 0;
    virtual void postRender() = 0;
    virtual void destroy() = 0;

protected:
    Context& context;
};
}