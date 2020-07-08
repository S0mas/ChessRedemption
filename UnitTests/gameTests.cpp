#include "pch.h"

class GameTests : public ::testing::Test

{

protected:

	virtual void TearDown()

	{

		//clean up all fake declaration after each test

		ISOLATOR_CLEANUP();

	}

};

TEST_F(GameTests, initialization) {
	Game game;
	EXPECT_EQ(game.result(), Result::NOT_STARTED);
	EXPECT_EQ(game.startingPlayer().color(), Player::Color::WHITE);
	EXPECT_EQ(game.activePlayer().color(), Player::Color::NONE);
}

TEST_F(GameTests, startGame) {
	Game game;
	game.start();
	EXPECT_EQ(game.result(), Result::ONGOING);
	EXPECT_EQ(game.startingPlayer().color(), Player::Color::WHITE);
	EXPECT_EQ(game.activePlayer().color(), Player::Color::WHITE);
}

TEST_F(GameTests, reset) {
	Game game;
	game.reset();
	EXPECT_EQ(game.result(), Result::NOT_STARTED);
	EXPECT_EQ(game.activePlayer().color(), Player::Color::NONE);
}

TEST_F(GameTests, setActivePlayer) {
	Game game;
	Player playerW(Player::Color::WHITE);
	Player playerB(Player::Color::BLACK);
	game.setActivePlayer(playerW);
	EXPECT_EQ(game.activePlayer().color(), playerW.color());
	game.setActivePlayer(playerB);
	EXPECT_EQ(game.activePlayer().color(), playerB.color());
	game.setActivePlayer(playerW);
	EXPECT_EQ(game.activePlayer().color(), playerW.color());
	EXPECT_NE(game.activePlayer().color(), playerB.color());
}

TEST_F(GameTests, setStartingPlayer) {
	Game game;
	Player playerW(Player::Color::WHITE);
	Player playerB(Player::Color::BLACK);
	EXPECT_EQ(game.startingPlayer().color(), playerW.color());
	game.setStartingPlayer(playerB);
	EXPECT_EQ(game.startingPlayer().color(), playerB.color());
	game.setStartingPlayer(playerW);
	EXPECT_EQ(game.startingPlayer().color(), playerW.color());
	EXPECT_NE(game.startingPlayer().color(), playerB.color());
}

TEST_F(GameTests, undoMove) {
	Chessboard* fakeChessboard = FAKE_ALL<Chessboard>();
	Game game;
	WHEN_CALLED(fakeChessboard->undoMove()).Return(true);
	EXPECT_EQ(game.activePlayer().color(), Player::Color::NONE);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Player::Color::WHITE);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Player::Color::BLACK);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Player::Color::WHITE);

	WHEN_CALLED(fakeChessboard->undoMove()).Return(false);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Player::Color::WHITE);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Player::Color::WHITE);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Player::Color::WHITE);
}
