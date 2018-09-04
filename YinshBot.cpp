#include "YinshBot.h"

YinshBot::YinshBot () {

}

YinshBot::YinshBot (int n, int m, int k, int l) {
	boardSize = n;
	totalRings = m;
	winningMarkers = k;
	ringsToWin = l;
	board = new Board(n);
}

void YinshBot::readCommand (string command) {

}

string YinshBot::findNextMove () {

}

bool YinshBot::checkGameEnd () {

}

double YinshBot::evalFunction (Board board) {

}
