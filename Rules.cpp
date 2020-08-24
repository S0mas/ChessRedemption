#include "Rules.h"

bool MoveValidator::wasMoveAccepted(SimpleMove const& simpleMove) const noexcept {
	return validateMove<Promotion, Move, Castling, EnPassant>(simpleMove);
}

bool MoveValidator::Move::isValid(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept {
	return chessboard.validPieceMove(simpleMove);
}

inline bool MoveValidator::Move::doMove(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept {
	return true;
}

inline bool MoveValidator::Promotion::isValid(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept {
	return chessboard.validPieceMove(simpleMove) &&
		chessboard.destinationIsLastRow(simpleMove.destination_) &&
		chessboard.specificPieceType(simpleMove.origin_, PieceType::PAWN);
}

inline bool MoveValidator::Promotion::doMove(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept {
	return true;
}

inline bool MoveValidator::Castling::isValid(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept {
	auto towerPos = Position(simpleMove.destination_.letter() == 'G' ? 'H' : 'A', simpleMove.origin_.number());
	return chessboard.pieceWasNotMoved(simpleMove.origin_) &&
		chessboard.specificPieceType(simpleMove.origin_, PieceType::KING) &&
		simpleMove.origin_.number() == simpleMove.destination_.number() &&
		(simpleMove.destination_.letter() == 'G' || simpleMove.destination_.letter() == 'C') &&
		chessboard.pieceWasNotMoved(towerPos) &&
		chessboard.noCollisionThroughMove(SimpleMove(simpleMove.origin_, towerPos).route());
}

inline bool MoveValidator::Castling::doMove(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept {
	return true;
}

inline bool MoveValidator::EnPassant::isValid(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept {
	auto column = simpleMove.destination_.letter();
	auto expectedOriginRow = simpleMove.origin_.number() == 4 ? 2 : 7;
	auto expectedDestinationRow = simpleMove.origin_.number();
	return chessboard.specificPieceType(simpleMove.origin_, PieceType::PAWN) &&
		chessboard.specificLastMove(SimpleMove(Position(column, expectedOriginRow), Position(column, expectedDestinationRow)), PieceType::PAWN) &&
		chessboard.possiblePieceCapture(simpleMove);
}

inline bool MoveValidator::EnPassant::doMove(SimpleMove const& simpleMove, Chessboard const& chessboard) noexcept {
	return true;
}
