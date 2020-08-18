#pragma once
#include "Move.h"
#include "Status.h"
#include "Chessboard.h"

class Rules {
	bool isThereCheck() const noexcept { return false; }
public:
	bool isMoveLegal(SimpleMove const& move) const noexcept { return false; }
	GameStatus gameStatus(Chessboard const& chessboard) const noexcept { return GameStatus::ONGOING; }
};