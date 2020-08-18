#include "Move.h"
#include "Chessboard.h"

bool FreePosition::operator()(Chessboard const& chessboard) const noexcept {
		return !chessboard.isPositionOccupied(position_);
}

bool EnemyAtPositionButKing::operator()(Chessboard const& chessboard) const noexcept  {
	return chessboard.isPositionOccupied(position_, expectedColor_) && !chessboard.isThereKing(position_);
}

bool NoCollisionThroughMove::operator()(Chessboard const& chessboard) const noexcept  {
	return !chessboard.isAnyPositionOccupied(positions_);
}


bool PieceWasNotMoved::operator()(Chessboard const& chessboard) const noexcept  {
	return chessboard.isPositionOccupied(position_) && !*chessboard.wasPieceMoved(position_);
}

bool SpecificLastMove::operator()(Chessboard const& chessboard) const noexcept  {
	return false;//chessboard.lastMove().simpleMove() == simpleMove_ && chessboard.lastMove().pieceType() == pieceType_;
}
