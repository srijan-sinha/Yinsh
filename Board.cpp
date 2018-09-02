#include "Board.h"

Board::Board ( ) {

}

Board::Board ( int size ) {

}

int Board::getBoardSize ( ) {
	return boardSize;
}

int Board::getNumRings ( ) {
	return numRings;
}

int Board::getNumOppRings ( ) {
	return numOppRings;
}

int Board::getNumDiscs ( ) {
	return numDiscs;
}

int Board::getNumOppDiscs ( ) {
	return numOppDiscs;
}

void Board::addRing ( int colour, int hexagonNum, int position ) {

}

void Board::moveRing ( int hexagon1, int position1, int hexagon2, int position2 ) {

}

void Board::removeRow ( int hexagon1, int position1, int hexagon2, int position2 ) {

}

void Board::removeRing ( int hexagonNum, int position );