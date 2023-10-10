#pragma once

#include "Grid.hpp"
#include "GridVisualizer.hpp"

namespace Console {
class ConsoleGridVisualizer : public Core::GridVisualizer {
public:
	explicit ConsoleGridVisualizer(const Core::Grid* const grid) noexcept;
	virtual ~ConsoleGridVisualizer() = default;
	
	virtual void display() noexcept override;

private:
	const Core::Grid* const grid;
};
}