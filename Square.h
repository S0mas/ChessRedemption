#pragma once
#include "Color.h"
#include "Piece.h"

class Square {
	Color color_;
	Piece* piece_ = nullptr;
public:
	bool isOccupied() const noexcept {
		return !piece_;
	}

	bool isFree() const noexcept {
		return piece_;
	}

	Piece* piece() const noexcept {
		return piece_;
	}
};