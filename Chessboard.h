#pragma once
#include <map>
#include <optional>
#include <algorithm>
#include "Move.h"
#include "Square.h"
#include "Position.h"
#include "Status.h"

class Chessboard {
	std::map<Position, Square> squares_;
	//SimpleMoveWithPiece lastMove_;

	Square const& square(Position const& position) const noexcept {
		return squares_.at(position);
	}

	Piece const& piece(Position const& position) const noexcept {
		return *square(position).piece();
	}
public:
	void reset() noexcept;
	void doMove(SimpleMove const& move) noexcept;
	bool undoMove() noexcept;

	bool isPositionOccupied(Position const& position) const noexcept {
		return square(position).isOccupied();
	}

	bool isPositionOccupied(Position const& position, Color const expected) const noexcept {
		return isPositionOccupied(position) && piece(position).color() == expected;
	}

	bool isAnyPositionOccupied(std::vector<Position> const& positions) const noexcept {
		return std::find_if(positions.begin(), positions.end(), [this](Position const& position) { return isPositionOccupied(position); }) != positions.end();
	}

	std::optional<bool> wasPieceMoved(Position const& position) const noexcept {
		return squares_.find(position) != squares_.end() ? std::optional{ piece(position).wasMoved() } : std::nullopt;
	}

	bool isThereKing(Position const& position) const noexcept {
		return isPositionOccupied(position) && piece(position).isKing();
	}

	bool isThereKing(Position const& position, Color const expected) const noexcept {
		return isThereKing(position) && piece(position).color() == expected;
	}

	//SimpleMoveWithPiece lastMove() const noexcept {
	//	return lastMove_;
	//}
};