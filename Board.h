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
		int numRings;
		int numOppRings;
		int numDiscs;
		int numOppDiscs;


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
		 * An empty constructor.
		 */
		Board();


		/**
		 * Generates an empty board of the given size.
		 * @param size is the size of the board, i.e. number of hexagons.
		 */
		Board(int size);


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
		 * @return the number of our bot's rings on board.
		 */
		int getNumRings();


		/**
		 * @return the number of opponent bot's rings on board.
		 */
		int getNumOppRings();


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
		 * Moves the ring from the initial location to the final location and adds 
		 * a disc in its place. also flips the disc in its path
		 * @param hexagon1 is the initial hexagon number of the ring.
		 * @param position1 is the initial position of the ring.
		 * @param hexagon2 is the final hexagon number of the ring.
		 * @param position2 is the final position of the ring.
		 */
		void moveRing(int hexagon1, int position1, int hexagon2, int position2);


		/**
		 * Removes the row between the start point and end point.
		 * @param hexagon1 is the hexagon number of the start point.
		 * @param position1 is the position of the start point.
		 * @param hexagon2 is the hexagon number of the end point.
		 * @param position2 is the position of the end point.
		 */
		void removeRow(int hexagon1, int position1, int hexagon2, int position2);


		/**
		 * Removes the ring at the marked location.
		 * @param hexagonNum is the hexagon number of the ring location.
		 * @param position is the position of the ring on the hexagon.
		 */
		void removeRing(int v, int l, int r);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 * @return truth value of neighbour exists.
		 */
		bool hasNextUp(int v, int l, int r);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 * @return truth value of neighbour exists.
		 */
		bool hasNextDown(int v, int l, int r);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 * @return truth value of neighbour exists.
		 */
		bool hasNextUpRight(int v, int l, int r);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 * @return truth value of neighbour exists.
		 */
		bool hasNextUpLeft(int v, int l, int r);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 * @return truth value of neighbour exists.
		 */
		bool hasNextDownRight(int v, int l, int r);


		/**
		 * @param v is the vertical line number on which the location is located.
		 * @param l is the diagonal line (bottom left to top right) number on which the location is located.
		 * @param r is the diagonal line (bottom right to top left) number on which the location is located.
		 * @return truth value of neighbour exists.
		 */
		bool hasNextDownLeft(int v, int l, int r);


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
}