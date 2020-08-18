#pragma once
#include <functional>
#include "Position.h"
#include "Color.h"

enum class PieceType {
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
};

class Piece {
	bool wasMoved_ = false;
	Color color_;
	PieceType type_;
public:
	virtual bool move(Position origin, Position destination, bool isAttack) = 0;

	virtual PieceType type() const noexcept = 0;

	virtual bool isKing() const noexcept {
		return false;
	}

	bool wasMoved() const noexcept {
		return wasMoved_;
	}

	Color color() const noexcept {
		return color_;
	}
};