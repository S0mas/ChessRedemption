#pragma once
#include "Move.h"

class Chessboard {
public:
	void reset() noexcept;
	void doMove(Move const& move) noexcept;
	bool undoMove() noexcept;
};