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
	EXPECT_EQ(game.status(), GameStatus::NOT_STARTED);
	EXPECT_EQ(game.startingPlayer().color(), Color::WHITE);
	EXPECT_EQ(game.activePlayer().color(), Color::NONE);
}

TEST_F(GameTests, startGame) {
	Game game;
	game.start();
	EXPECT_EQ(game.status(), GameStatus::ONGOING);
	EXPECT_EQ(game.startingPlayer().color(), Color::WHITE);
	EXPECT_EQ(game.activePlayer().color(), Color::WHITE);
}

TEST_F(GameTests, reset) {
	Game game;
	game.reset();
	EXPECT_EQ(game.status(), GameStatus::NOT_STARTED);
	EXPECT_EQ(game.activePlayer().color(), Color::NONE);
}
TEST_F(GameTests, undoMove) {
	Chessboard* fakeChessboard = FAKE_ALL<Chessboard>();
	Game game;
	WHEN_CALLED(fakeChessboard->undoMove()).Return(true);
	EXPECT_EQ(game.activePlayer().color(), Color::NONE);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Color::WHITE);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Color::BLACK);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Color::WHITE);

	WHEN_CALLED(fakeChessboard->undoMove()).Return(false);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Color::WHITE);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Color::WHITE);
	game.undo();
	EXPECT_EQ(game.activePlayer().color(), Color::WHITE);
}

TEST_F(GameTests, tryMove) {
	//Chessboard* fakeChessboard = FAKE_ALL<Chessboard>();
	Rules* fakeRules = FAKE_ALL<Rules>();
	Game* fakeGame = FAKE_ALL<Game>();
	Game* game = new Game;
	SimpleMove move(Position::createPosition<'A', 1>(), Position::createPosition<'B', 1>());
	WHEN_CALLED(fakeRules->isMoveLegal(move)).Return(true);
	
}
TEST_F(GameTests, positionCreation) {
	auto p1 = Position::createPosition<'A', 1>();



}
