#pragma once
#include "Move.h"
#include "Player.h"
#include "Result.h"
#include "Chessboard.h"
#include "Pieces.h"
#include "Rules.h"
#include <memory>
#include <vector>
#include <string>

class Game {
	Player white_{Player::Color::WHITE};
	Player black_{Player::Color::BLACK};
	Player const* startingPlayer_ = &white_;
	Player const* activePlayer_ = nullptr;
	Result result_ = Result::NOT_STARTED;
	std::unique_ptr<Chessboard> chessboard_ = std::make_unique<Chessboard>();
	std::unique_ptr<Rules> rules_ = std::make_unique<Rules>();
	std::unique_ptr<Pieces> pieces_ = std::make_unique<Pieces>();


	void switchActivePlayer() noexcept;
	void updateGameResult() noexcept;
	bool hasGameEnded() noexcept;
public:
	Game() {}
	void start() noexcept;
	void reset() noexcept;
	bool tryToMove(Move const& move) noexcept;
	void undo() noexcept;
	void setActivePlayer(Player const& player) noexcept;
	void setStartingPlayer(Player const& player) noexcept;
	Player startingPlayer() const noexcept;
	Player activePlayer() const noexcept;
	Result result() const noexcept;
};