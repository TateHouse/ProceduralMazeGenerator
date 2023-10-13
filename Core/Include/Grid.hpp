#pragma once

#include "Cell.hpp"

namespace Core {
class Grid {
public:
	virtual ~Grid() noexcept = 0;

public:
	virtual Cell* operator[](const std::pair<const int, const int>& position) noexcept = 0;
	virtual const Cell* const getCell(const std::pair<const int, const int>& position) const noexcept = 0;

public:
	virtual void initialize() noexcept = 0;
	[[nodiscard]] virtual const std::pair<const int, const int> getSize() const noexcept = 0;
};
}