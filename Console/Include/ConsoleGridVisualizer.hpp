#pragma once

#include "Grid.hpp"
#include "GridVisualizer.hpp"

namespace Console {
class ConsoleGridVisualizer : public Core::GridVisualizer {
public:
	explicit ConsoleGridVisualizer(const Core::Grid* const grid) noexcept;
    ConsoleGridVisualizer(const ConsoleGridVisualizer&) = delete;
    ConsoleGridVisualizer(ConsoleGridVisualizer&&) = delete;
	virtual ~ConsoleGridVisualizer() = default;

public:
    ConsoleGridVisualizer& operator=(const ConsoleGridVisualizer&) = delete;
    ConsoleGridVisualizer& operator=(ConsoleGridVisualizer&&) = delete;

public:
    virtual void visualize() const noexcept override;

private:
	const Core::Grid* const grid;
};
}