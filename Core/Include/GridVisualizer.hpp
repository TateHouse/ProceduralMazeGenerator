#pragma once

namespace Core {
class GridVisualizer {
public:
    virtual ~GridVisualizer() noexcept = default;

public:
    virtual void visualize() const noexcept = 0;
};
}