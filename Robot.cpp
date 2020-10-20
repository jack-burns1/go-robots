/* Jack Burns
 * Comp 15
 * 16 October, 2019
 * Robot.cpp
 */

#include "Robot.h"

Robot::Robot()
{
	symbol = ' ';
	curr_row = -1;
	curr_col = -1;
}

void Robot::update_pos(int row, int col)
{
	curr_row = row;
	curr_col = col;
}

void Robot::change_symbol(char c)
{
	symbol = c;
}

char Robot::return_symbol()
{
	return symbol;
}
void Robot::add_to_board(Board &b)
{
	b.add_robot(symbol, curr_row, curr_col);
}