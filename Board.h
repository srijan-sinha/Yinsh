#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Board {
	
	private:
		
		int *** board;		//	0 -> Not Occupied	1 -> Our Ring 	-1 -> Opponent's Ring 	2 -> Our Disc 	-2 -> Opponent's Disc 

		int boardSize;
		int maxRings;
		int sequenceLength;
		int ringsToWin;

		int numRings;
		int numOppRings;
		
		int ringsScored;
		int oppRingsScored;
		
		int numDiscs;
		int numOppDiscs;
		
		vector<int> ringV;
		vector<int> ringL;
		vector<int> ringR;

		vector<int> ringV_opp;
		vector<int> ringL_opp;
		vector<int> ringR_opp;

		/**
		 * Convert coordinate (h, p) to (v, l, r)
		 * @param hexagonNum is the hexagon number of the location.
		 * @param position is the position of the location on the hexagon.
		 * @param v is the respective vertical line number on which the location is located.
		 * @param l is the respective diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the respective vertical line (bottom right to top left) number on which the location is located.
		 */
		void convertTo(int hexagonNum, int position, int v, int l, int r);


		/**
		 * Convert coordinate (v, l, r) to (h, p)
		 * @param v is the respective vertical line number on which the location is located.
		 * @param l is the respective diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the respective vertical line (bottom right to top left) number on which the location is located.
		 * @param hexagonNum is the hexagon number of the location.
		 * @param position is the position of the location on the hexagon.
		 */
		void convertBack(int v, int l, int r, int hexagonNum, int position);


	public:

		/**
		 * Empty constructor.
		 */
		Board();


		/**
		 * Generates an empty board of the given size.
		 * @param size is the size of the board, i.e. number of hexagons.
		 */
		Board(int n, int m, int k, int l);


		/**
		 * Initializes the 2-D board array.
		 * @param size is the number of hexagons on the board.
		 */
		void initBoard(int size);


		/**
		 * @return the board size.
		 */
		int getBoardSize();

		/**
		 * @return the total rings to be played with.
		 */
		int getMaxRings();


		/**
		 * @return the number of discs to be placed in a line.
		 */
		int getSequenceLength();

		/**
		 * @return the number of rings to be taken off the board for a win.
		 */
		int getRingsToWin();


		/**
		 * @return the number of our bot's rings on board.
		 */
		int getNumRings();


		/**
		 * @return the number of opponent bot's rings on board.
		 */
		int getNumOppRings();


		/**
		 * @return the number of our bot's rings scored till now.
		 */
		int getRingsScored();


		/**
		 * @return the number of opponent bot's rings scored till now.
		 */
		int getOppRingsScored();


		/**
		 * @return number of our bot's discs on board.
		 */
		int getNumDiscs();


		/**
		 * @return number of opponent bot's discs on board.
		 */
		int getNumOppDiscs();


		/**
		 * Adds a ring of the given colour at the mentioned location on the board.
		 * @param colour is 1 for our colour and -1 for opponents colour.
		 * @param hexagonNum is the distance of the point from the centre of the board.
		 * @param position is the point number on the circumference of the hexagon.
		 */
		void addRing(int colour, int hexagonNum, int position);


		/**
		 * Undoes addition of a ring at the mentioned location on the board.
		 * @param hexagonNum is the distance of the point from the centre of the board.
		 * @param position is the point number on the circumference of the hexagon.
		 */
		void undoAddRing(int hexagonNum, int position);


		/**
		 * Moves the ring from the initial location to the final location and adds 
		 * a disc in its place also flips the disc in its path.
		 * @param hexagon1 is the initial hexagon number of the ring.
		 * @param position1 is the initial position of the ring.
		 * @param hexagon2 is the final hexagon number of the ring.
		 * @param position2 is the final position of the ring.
		 */
		void moveRing(int hexagon1, int position1, int hexagon2, int position2);


		/**
		 * Undoes all effects of movement of the ring from the initial location(1) to the final location(2).
		 * @param hexagon1 is the initial hexagon number of the ring.
		 * @param position1 is the initial position of the ring.
		 * @param hexagon2 is the final hexagon number of the ring.
		 * @param position2 is the final position of the ring.
		 */
		void undoMoveRing(int hexagon1, int position1, int hexagon2, int position2);


		/**
		 * Removes the row between the start point and end point.
		 * @param hexagon1 is the hexagon number of the start point.
		 * @param position1 is the position of the start point.
		 * @param hexagon2 is the hexagon number of the end point.
		 * @param position2 is the position of the end point.
		 */
		void removeRow(int hexagon1, int position1, int hexagon2, int position2);


		/**
		 * Adds back discs of the input colour between the given locations(both inclusive).
		 * @param colour is the colour of the discs to be added back.
		 * @param hexagon1 is the hexagon number of the start point.
		 * @param position1 is the position of the start point.
		 * @param hexagon2 is the hexagon number of the end point.
		 * @param position2 is the position of the end point.
		 */
		void undoRemoveRow(int colour, int hexagon1, int position1, int hexagon2, int position2);


		/**
		 * Removes the ring at the marked location.
		 * @param colour is the colour of the ring to be added.
		 * @param hexagonNum is the hexagon number of the ring location.
		 * @param position is the position of the ring on the hexagon.
		 */
		void removeRing(int colour, int hexagonNum, int position);


		/**
		 * Adds back ring of the given colour at the marked location.
		 * @param colour is the colour of the ring to be added back.
		 * @param hexagonNum is the hexagon number of the ring location.
		 * @param position is the position of the ring on the hexagon.
		 */
		void undoRemoveRing(int colour, int hexagonNum, int position);


		/**
		 * Generates all possible moves on the board for the given player.
		 * @param perspective is 1 for our turn and -1 for opponent's turn.
		 * @return vector<string> in which each element is a command which can be executed in the given board configuration.
		 */
		vector<string> generateMoveList(int perspective);


		/**
		 * Appends all possible moves for a ring addition to the current board configuration.
		 */
		void addRingMoves(vector<string> moves);


		/**
		 * Appends all possible ring movements for the given ring at the given location .
		 * @param moves is the vector to which the rings are to be appended.
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 */
		void moveRingMoves(vector<string> moves, int v, int l, int r);


		/**
		 * Checks if the given coordinates are valid.
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 */
		bool check(int v, int l, int r);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 */
		void nextUp(int v, int l, int r);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 */
		void nextDown(int v, int l, int r);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 */
		void nextUpRight(int v, int l, int r);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 */
		void nextUpLeft(int hexagonNum, int position);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 */
		void nextDownRight(int hexagonNum, int position);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 */
		void nextDownLeft(int hexagonNum, int position);

		void print_board();
}