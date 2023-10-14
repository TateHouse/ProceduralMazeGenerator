#pragma once

#include "Grid.hpp"
#include "GridVisualizer.hpp"

namespace Console {
class ConsoleMazeVisualizer : public Core::GridVisualizer {
public:
	explicit ConsoleMazeVisualizer(const Core::Grid* const grid) noexcept;
	virtual ~ConsoleMazeVisualizer() = default;
	
	virtual void visualize() noexcept override;

private:
	const Core::Grid* const grid;
};
}