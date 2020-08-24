#pragma once
#include "Position.h"
#include <algorithm>
#include <vector>

struct SimpleMove {
	Position origin_;
	Position destination_;

	SimpleMove(Position o, Position d) : origin_(o), destination_(d) {}

	std::vector<Position> route() const noexcept {
		return {};
	}
};

inline bool operator==(SimpleMove const& lhs, SimpleMove const& rhs) noexcept {
	return lhs.origin_ == rhs.origin_ && lhs.destination_ == rhs.destination_;
}
