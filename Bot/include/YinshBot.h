#ifndef YINSH_H
#define YINSH_H

#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
/**
 * Uncomment for the following libraries
#include <ctime>
#include <cmath>
#include <algorithm>
 */
using namespace std;

#include "Board.h"

class YinshBot {
	
	public:

		Board * board;
		int boardSize;
		int maxRings;
		int SequenceLength;
		int ringsToWin;
		int turn;	//	1 for our, -1 for opponent's
		int numPlays;
		int init_depth = 0;
		vector<double> w;
		double weightsSum = 0;
		int eff = 0;

	
		/**
		 * Empty Constructor.
		 */
		YinshBot();


		/**
		 * Sets up the game with the argument values.
		 * @param n is the board size.
		 * @param m is the starting number of rings with each bot.
		 * @param k is the number of markers in a line required to remove a ring.
		 * @param l is the number of rings to be removed to win.
		 */
		YinshBot(int n, int m, int k, int l, int startTurn);


		/**
		 * Reads the input string command and executes the respective command.
		 * @param command is the input command. 
		 */
		


		/**
		 * Generates the next move after opponent bot's play and executes it.
		 * @return the command to send to the server.
		 */
		string findNextMove(int depth);
		void print_board();
		void executeCommand(string s, int perspective);

		void undoCommand(string s, int perspective);

	
		double miniMax(int depth, int perspective, vector<string>& bestMoves, double a, double b);

		void changeTurn();
		vector<string> moveList(int perspective);
		int getRingVLR(int perspective, int vlr, int i);
		int ringAttacks();

		/**
		 * Checks if the game has ended after each ply.
		 * @return true when the game ends.
		 */
		bool checkGameEnd();


		/**
		 * Calculates the evaluation of any configuration of the board.
		 * @param board contains the configuration of the Board.
		 * @return a double which has the likability of the current board configuration.
		 */
		double evalFunction();
		double sigmoid(double eval);
		vector<double> getWeights ();
		vector<double> getFeatures (double &min, double &max);	


};
#endif