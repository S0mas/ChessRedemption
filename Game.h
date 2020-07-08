#pragma once
#include "Move.h"
#include "Player.h"
#include "Result.h"

class Game {
public:
	void start();
	void reset();
	bool move(Move const& move);
	void undo();
	void setStartingPlayer(Player const& player);
	Result gameResult();
};