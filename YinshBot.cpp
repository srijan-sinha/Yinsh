#include "YinshBot.h"

YinshBot::YinshBot () {

}

YinshBot::YinshBot (int n, int m, int k, int l) {
	boardSize = n;
	maxRings = m;
	sequenceLength = k;
	ringsToWin = l;
	board = new Board(n, m, k, l);
}

void YinshBot::readCommand (string command) {

}

string YinshBot::findNextMove () {

}

bool YinshBot::checkGameEnd () {

}

double YinshBot::evalFunction (Board board) {
	
}
