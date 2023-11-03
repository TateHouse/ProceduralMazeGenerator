#pragma once

#include "InputComponent.hpp"

namespace Renderer {
class OrthographicCameraInput : public InputComponent {
public:
    explicit OrthographicCameraInput(Context& context) noexcept: InputComponent {context} {

    }

    virtual ~OrthographicCameraInput() noexcept = default;

public:
    virtual void initialize() override;
    virtual void postInitialize() override;
    virtual void update() override;
    virtual void postUpdate() override;
    virtual void render() override;
    virtual void postRender() override;
    virtual void destroy() override;

public:
    virtual void onKeyDown() override;

private:
    float moveSpeed {0.0075f};
    float rotationSpeed {0.0075f};
};
}