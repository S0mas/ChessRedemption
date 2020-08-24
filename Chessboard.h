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
	SimpleMove* lastMove_ = nullptr;

	Square const& square(Position const& position) const noexcept {
		return squares_.at(position);
	}

	Piece const& piece(Position const& position) const noexcept {
		return *square(position).piece();
	}

	Piece& piece(Position const& position) noexcept {
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

	bool isPieceMoveValid(SimpleMove const& move) const noexcept {
		auto isAttack = piece(move.origin_).color() != piece(move.destination_).color();
		return piece(move.origin_).isValidMove(move, isAttack)
			&& (isAttack || !isPositionOccupied(move.destination_))
			&& !isThereKing(move.destination_)
			&& (piece(move.origin_).movesThroughCollisions() || !isAnyPositionOccupied(move.route()));
	}

	bool isPieceCapturePossible(SimpleMove const& move) const noexcept {
		return piece(move.origin_).isValidMove(move, true)
			&& (piece(move.origin_).movesThroughCollisions() || !isAnyPositionOccupied(move.route()));
	}

	bool isPieceType(Position const& position, PieceType const pieceType) const noexcept {
		return isPositionOccupied(position) && piece(position).type() == pieceType;
	}

	SimpleMove lastMove() const noexcept {
		return *lastMove_;
	}

	PieceType lastMovedPieceType() const noexcept {
		return piece(lastMove_->destination_).type();
	}

	///CONDITIONS

	bool validPieceMove(SimpleMove const& move) const noexcept {
		return isPieceMoveValid(move);
	}

	bool possiblePieceCapture(SimpleMove const& move)  const noexcept {
		return isPieceCapturePossible(move);
	}

	bool noCollisionThroughMove(std::vector<Position> const& positions)  const noexcept {
		return !isAnyPositionOccupied(positions);
	}

	bool pieceWasNotMoved(Position const& pos) const noexcept {
		return isPositionOccupied(pos) && !*wasPieceMoved(pos);
	}

	bool destinationIsLastRow(Position const& pos) const noexcept {
		return pos.isLastRow();
	}

	bool specificLastMove(SimpleMove const& move, PieceType const pieceType) const noexcept {
		return lastMove() == move && lastMovedPieceType() == pieceType;
	}

	bool specificPieceType(Position const& pos, PieceType const pieceType) const noexcept {
		return isPieceType(pos, pieceType);
	}
};