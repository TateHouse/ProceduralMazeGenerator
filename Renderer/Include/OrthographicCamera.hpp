#pragma once

#include <glm/glm.hpp>

#include "Component.hpp"
#include "OrthographicCameraDefaults.hpp"

namespace Renderer {
class OrthographicCamera : public Component {
public:
    OrthographicCamera(Context& context,
                       const float left,
                       const float right,
                       const float bottom,
                       const float top,
                       const float near = -1.0f,
                       const float far = 1.0f) noexcept;

public:
    virtual void initialize() override;
    virtual void postInitialize() override;
    virtual void update() override;
    virtual void postUpdate() override;
    virtual void render() override;
    virtual void postRender() override;
    virtual void destroy() override;

public:
    [[nodiscard]] const glm::mat4& getProjection() const noexcept;
    [[nodiscard]] const glm::mat4& getView() const noexcept;
    [[nodiscard]] const glm::mat4& getViewProjection() const noexcept;
    [[nodiscard]] const glm::vec3& getPosition() const noexcept;
    void setPosition(const glm::vec3& position) noexcept;
    [[nodiscard]] const float getRotation() const noexcept;
    void setRotation(const float rotation) noexcept;
    [[nodiscard]] const float getZoomLevel() const noexcept;
    void setZoomLevel(const float zoomLevel) noexcept;

private:
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;
    glm::mat4 projection;
    glm::mat4 view {glm::mat4(1.0f)};
    glm::mat4 viewProjection;
    bool isDirty {true};
    glm::vec3 position {OrthographicCameraDefaults::getDefaultPosition()};
    float rotation {OrthographicCameraDefaults::getDefaultRotation()};
    float zoomLevel {OrthographicCameraDefaults::getDefaultZoomLevel()};
};
}