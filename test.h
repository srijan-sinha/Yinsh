#ifndef TEST_H
#define TEST_H

#include <string>
#include <iostream>
#include <vector>
/**
 * Uncomment for the following libraries
#include <ctime>
#include <cmath>
#include <algorithm>
 */
using namespace std;


class test {
	private:
		int boardSize = 5;
		int*** board;
		int numRings=0,numOppRings=0;
		int numDiscs,numOppDiscs;
		int ringsScored,oppRingsScored;
		vector<int> ringV,ringR,ringL,ringV_opp,ringR_opp,ringL_opp;
		int sequenceLength = 5;
		int ringsToWin = 5;
		
	public:

		/**
		 * Empty Constructor.
		 */
		YinshBot();
		
}