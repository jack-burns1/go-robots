/* Jack Burns
 * Comp 15
 * 16 October, 2019
 * Robot.h
 */

#include <iostream>
#include "Board.h"

using namespace std;

#ifndef _ROBOT_H_
#define _ROBOT_H_

class Robot
{
public:

	Robot();

	void update_pos(int row, int col);
	void change_symbol(char c);
	char return_symbol();
	void add_to_board(Board &b);


private:

	char symbol;
	int curr_row;
	int curr_col;

};

#endif