#pragma once
#include "Color.h"

class Player {
public:
private:
	Color color_;
public:
	Player() : color_(Color::NONE) {}
	Player(Color const color) : color_(color) {}
	Color color() const noexcept {
		return color_;
	}
};