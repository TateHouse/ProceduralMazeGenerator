#pragma once

namespace Core {
class GridVisualizer {
public:
	virtual ~GridVisualizer() noexcept = default;
	
	virtual void visualize() noexcept = 0;
};
}