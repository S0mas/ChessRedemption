#pragma once
#include "Move.h"
#include "Status.h"
#include <memory>
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include "Chessboard.h"

class MoveValidator {
	Chessboard& chessboard_;

	class Promotion {
	public:
		static bool isValid(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept;
		static bool doMove(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept;
	};

	class Move {
	public:
		static bool isValid(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept;
		static bool doMove(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept;
	};

	class Castling {
	public:
		static bool isValid(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept;
		static bool doMove(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept;
	};

	class EnPassant {
	public:
		static bool isValid(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept;
		static bool doMove(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept;
	};

	template <typename T>
	bool validateMove(SimpleMove const& simpleMove) const noexcept { return false; }

	template <typename T, typename NextT, typename... Rest>
	bool validateMove(SimpleMove const& simpleMove) const noexcept {
		if (T::isValid(simpleMove, chessboard_))
			return T::doMove(simpleMove, chessboard_);
		return validateMove<NextT, Rest...>(simpleMove);
	}

	bool isThereCheck() const noexcept { return false; }
public:
	MoveValidator(Chessboard& chessboard) : chessboard_(chessboard) {}
	bool wasMoveAccepted(SimpleMove const& simpleMove) const noexcept;
	GameStatus gameStatus(Chessboard const& chessboard) const noexcept { return GameStatus::ONGOING; }
};

