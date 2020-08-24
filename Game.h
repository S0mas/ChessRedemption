#pragma once
#include "Move.h"
#include "Player.h"
#include "Status.h"
#include "Chessboard.h"
#include "Pieces.h"
#include "Rules.h"
#include <memory>
#include <vector>
#include <string>

class Game {
	Player white_{Color::WHITE};
	Player black_{Color::BLACK};
	Player const& startingPlayer_ = white_;
	Player const* activePlayer_ = nullptr;
	Pieces pieces_;
	Chessboard chessboard_;
	MoveValidator rules_{ chessboard_ };

	void switchActivePlayer() noexcept;
	bool hasGameEnded() noexcept;
public:
	Game() {}
	void start() noexcept;
	void reset() noexcept;
	bool move(SimpleMove const& move) noexcept;
	void undo() noexcept;
	Player startingPlayer() const noexcept;
	Player activePlayer() const noexcept;
	GameStatus status() const noexcept;
};