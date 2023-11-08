#pragma once

#include "Grid.hpp"
#include "GridVisualizer.hpp"

namespace Console {
class ConsoleMazeVisualizer : public Core::GridVisualizer {
public:
	explicit ConsoleMazeVisualizer(const Core::Grid* const grid) noexcept;
    ConsoleMazeVisualizer(const ConsoleMazeVisualizer&) = delete;
    ConsoleMazeVisualizer(ConsoleMazeVisualizer&&) = delete;
	virtual ~ConsoleMazeVisualizer() = default;

public:
    ConsoleMazeVisualizer& operator=(const ConsoleMazeVisualizer&) = delete;
    ConsoleMazeVisualizer& operator=(ConsoleMazeVisualizer&&) = delete;

public:
    virtual void visualize() const noexcept override;

private:
	const Core::Grid* const grid;
};
}