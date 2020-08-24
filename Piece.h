#pragma once
#include <functional>
#include "Position.h"
#include "Color.h"
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
	virtual bool isValidMove(SimpleMove const& move, bool isAttack) const noexcept = 0;

	virtual PieceType type() const noexcept = 0;

	virtual bool isKing() const noexcept {
		return false;
	}

	virtual bool movesThroughCollisions() const noexcept {
		return false;
	}

	bool wasMoved() const noexcept {
		return wasMoved_;
	}

	void setWasMoved(bool const wasMoved) noexcept {
		wasMoved_ = wasMoved;
	}

	Color color() const noexcept {
		return color_;
	}


};