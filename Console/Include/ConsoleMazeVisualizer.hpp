#pragma once

#include "Grid.hpp"
#include "GridVisualizer.hpp"

namespace Console {
class ConsoleMazeVisualizer : public Core::GridVisualizer {
public:
	explicit ConsoleMazeVisualizer(const Core::Grid* const grid) noexcept;
	virtual ~ConsoleMazeVisualizer() = default;

public:
    virtual void visualize() const noexcept override;

private:
	const Core::Grid* const grid;
};
}