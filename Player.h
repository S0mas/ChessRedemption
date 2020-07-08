#pragma once

class Player {
public:
	enum class Color {
		WHITE,
		BLACK,
		NONE
	};
private:
	Color color_;
public:
	Player() : color_(Color::NONE) {}
	Player(Color const color) : color_(color) {}
	Color color() const noexcept {
		return color_;
	}
};