#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

using namespace std;

class Board {
	
	private:
		
		int ** board;
		int boardSize;
		int numRings;
		int numOppRings;
		int numDiscs;
		int numOppDiscs;

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
		int getNumDiscs();


		/**
		 * Adds a ring of the given colour at the mentioned location on the board.
		 * @param colour is 1 for our colour and -1 for opponents colour.
		 * @param hexagonNum is the distance of the point from the centre of the board.
		 * @param position is the point number on the circumference of the hexagon.
		 */
		void addRing(int colour, int hexagonNum, int position);


		/**
		 * Moves the ring from the initial location to the final location and adds 
		 * a disc in its place.
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
		void removeRing(int hexagonNum, int position);

}