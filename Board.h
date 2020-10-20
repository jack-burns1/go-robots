/* Jack Burns
 * Comp 15
 * 14 October, 2019
 * board.h
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> //remove() [to remove spaces in line] - could have done					
#include <fstream>   // with a loop but  remove() is less code

using namespace std;

#ifndef _BOARD_H_
#define _BOARD_H_

const int LEN = 8;
const int WID = 8;
const char OPEN = 'X';
const char VER = '|';
const char HOR = '-';
const char EDGE = 'W';
const char DONE = '*';


struct Cell {
	bool north;
	bool south;
	bool east;
	bool west;
	bool goal;
	char symbol;
};

class Board
{
public:

	Board();

	void read_in_board(string filename);
	void fill_cells();
	void print_board();
	void check_north(Cell &i, int row, int col);
	void check_south(Cell &i, int row, int col);
	void check_east(Cell &i, int row, int col);
	void check_west(Cell &i, int row, int col);
	void create_board(Cell &i, int row, int col);

	Cell* cell_at(int rrow, int rcol);
	bool is_over();
	void add_robot(char sym, int row, int col);
	void update_robot();

	void move_up();
	void move_down();
	void move_left();
	void move_right();
	void remove_robot();
	int get_robo_row();
	int get_robo_col();
	void manual_move_robot(int row, int col);	

private:

	// 2d array representing the gameboard
	Cell game[LEN][WID];
	// pointer to element in 2d array representing board with ALL chars
	char preGame[LEN * 2 - 1][WID * 2 - 1];

	bool winner;
	int robo_row;
	int robo_col;
	char rSymbol;
};

#endif

