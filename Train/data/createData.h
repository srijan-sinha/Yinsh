#ifndef CREATEDATA_H
#define CREATEDATA_H

#include <bits/stdc++.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class createData {

	public:

		int boardSize;
		int maxRings;
		int sequenceLength;
		int ringsToWin;

		int *** translatedBoard;
		
		createData(int n, int m, int k, int l);
		void initTranslatedBoard();
		void convertBack (int v, int l, int r, int& hexagonNum, int& position);
		bool check(int v, int l, int r);
		void translate(int[][][] board);
		int index(int h, int p);

};

#endif