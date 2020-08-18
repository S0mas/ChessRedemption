#pragma once
#include "Position.h"
#include "Piece.h"
#include <vector>

class Chessboard;

struct SimpleMove {
	Position origin_;
	Position destination_;

	SimpleMove(Position o, Position d) : origin_(o), destination_(d) {}
};

inline bool operator==(SimpleMove const& lhs, SimpleMove const& rhs) noexcept {
	return lhs.origin_ == rhs.origin_ && lhs.destination_ == rhs.destination_;
}

struct SimpleMoveWithPiece {
	SimpleMove simpleMove_;
	Piece* piece_;

	SimpleMove simpleMove() const noexcept {
		return simpleMove_;
	}

	PieceType pieceType() const noexcept {
		return piece_->type();
	}
};

class AbstractPrecondition {
public:
	virtual bool operator()(Chessboard const& chessboard) const noexcept = 0;
};

class FreePosition : public AbstractPrecondition {
	Position position_;
public:
	bool operator()(Chessboard const& chessboard) const noexcept override;
};

class EnemyAtPositionButKing : public AbstractPrecondition {
	Position position_;
	Color expectedColor_;
public:
	bool operator()(Chessboard const& chessboard) const noexcept override;
};

class NoCollisionThroughMove : public AbstractPrecondition {
	std::vector<Position> positions_;
public:
	bool operator()(Chessboard const& chessboard) const noexcept override;
};

class PieceWasNotMoved : public AbstractPrecondition {
	Position position_;
public:
	bool operator()(Chessboard const& chessboard) const noexcept override;
};

class SpecificLastMove : public AbstractPrecondition {
	SimpleMove simpleMove_;
	PieceType pieceType_;
public:
	bool operator()(Chessboard const& chessboard) const noexcept override;
};

class AbstractMove {
protected:
	SimpleMove simpleMove_;
public:
	virtual std::vector<AbstractPrecondition*> preconditions() const noexcept = 0;
	virtual void additionalActions() = 0;
	virtual std::vector<Position> positionsToCheckCollision() = 0; // different for Knight and for Castling
};

class Move : public AbstractMove {
public:
	std::vector<AbstractPrecondition*> preconditions() const noexcept override {
		return std::vector<AbstractPrecondition*>{};
	}
};

class Promotion : public AbstractMove {
public:
	std::vector<AbstractPrecondition*> preconditions() const noexcept override {
		return std::vector<AbstractPrecondition*>{};
	}
};

class Capture : public AbstractMove {
public:
	std::vector<AbstractPrecondition*> preconditions() const noexcept override {
		return std::vector<AbstractPrecondition*>{};
	}
};


class Castling : public AbstractMove {
public:
	std::vector<AbstractPrecondition*> preconditions() const noexcept override {
		return std::vector<AbstractPrecondition*>{};
	}
};

class EnPassant : public AbstractMove {
public:
	std::vector<AbstractPrecondition*> preconditions() const noexcept override {
		return std::vector<AbstractPrecondition*>{};
	}
};