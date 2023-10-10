#pragma once

namespace Core {
class GridVisualizer {
public:
	virtual ~GridVisualizer() noexcept = default;
	
	virtual void display() noexcept = 0;
};
}