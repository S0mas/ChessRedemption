#include "Game.h"

void Game::switchActivePlayer() noexcept {
	activePlayer_ = activePlayer_ == &white_ ? &black_ : &white_;
}

bool Game::hasGameEnded() noexcept {
	return status() != GameStatus::ONGOING && status() != GameStatus::NOT_STARTED;
}

void Game::start() noexcept {
	activePlayer_ = &startingPlayer_;
}

void Game::reset() noexcept {
	chessboard_.reset();
	pieces_.reset();
	activePlayer_ = nullptr;
}

bool Game::tryToMove(SimpleMove const& move) noexcept {
	if (rules_.isMoveLegal(move)) {
		chessboard_.doMove(move);
		if(!hasGameEnded())
			switchActivePlayer();
		return true;
	}
	return false;
}

void Game::undo() noexcept {
	if(chessboard_.undoMove())
		switchActivePlayer();
}

Player Game::startingPlayer() const noexcept {
	return startingPlayer_;
}

Player Game::activePlayer() const noexcept {
	return activePlayer_ ? *activePlayer_ : Player();
}

GameStatus Game::status() const noexcept {
	return activePlayer_ ? rules_.gameStatus(chessboard_) : GameStatus::NOT_STARTED;
}
