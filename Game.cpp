#include "Game.h"

void Game::switchActivePlayer() noexcept {
	activePlayer_ = activePlayer_ == &white_ ? &black_ : &white_;
}

void Game::updateGameResult() noexcept {
}

bool Game::hasGameEnded() noexcept {
	updateGameResult();
	return result_ != Result::ONGOING;
}

void Game::start() noexcept {
	activePlayer_ = startingPlayer_;
	result_ = Result::ONGOING;
}

void Game::reset() noexcept {
	chessboard_->reset();
	pieces_->reset();
	activePlayer_ = nullptr;
	result_ = Result::NOT_STARTED;
}

bool Game::tryToMove(Move const& move) noexcept {
	auto result = rules_->isMoveLegal(move);
	if (result) {
		chessboard_->doMove(move);
		if(!hasGameEnded())
			switchActivePlayer();
	}
	return result;
}

void Game::undo() noexcept {
	if(chessboard_->undoMove())
		switchActivePlayer();
}

void Game::setActivePlayer(Player const& player) noexcept {
	activePlayer_ = &player;
}

void Game::setStartingPlayer(Player const& player) noexcept {
	startingPlayer_ = &player;
}

Player Game::startingPlayer() const noexcept {
	return *startingPlayer_;
}

Player Game::activePlayer() const noexcept {
	return activePlayer_ ? *activePlayer_ : Player();
}

Result Game::result() const noexcept {
	return result_;
}
