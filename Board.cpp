/* Jack Burns
 * Comp 15
 * 14 October, 2019
 * board.h
 */

#include "Board.h"


// Default constructor
// Initializes pre-game board;
Board::Board()
{ 
	for (int i = 0; i < LEN * 2 - 1; i++) {
		for (int j = 0; j < WID * 2 - 1; j++) {
			preGame[i][j] = ' ';
		}
	}
	winner = false;
	robo_row = -1;
	robo_col = -1;
	rSymbol = ' ';
}
// read_in_board
// Parameters: string name of the file
// Returns: Nothing
// Does: opens the file and fills the pre-game board with the exact input
void Board::read_in_board(string filename)
{
	ifstream infile;
	infile.open(filename);
	if (!infile) {
		cout << "Cannot open " << filename << endl;
		return;
	}
	string line;
	for (int j = 0; j < 2 * LEN - 1; j++) {
		getline(infile, line);
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		for (int i = 0; i < 2 * WID - 1; i++) {
			preGame[j][i] = line[i];
		}
	}
	fill_cells();
	infile.close();
}
// fill_cells
// Parameters: None.
// Returns: Nothing.
// Does: Uses pre-game board to fill the cell structs in the game board
void Board::fill_cells()
{

	for (int j = 0; j < 2 * LEN - 1; j = j + 2) {
		for (int i = 0; i < 2 * WID - 1; i = i + 2) {
			Cell newcell;
			newcell.north = false;
			newcell.south = false;
			newcell.east = false;
			newcell.west = false;
			newcell.symbol = preGame[j][i];
			if (newcell.symbol == DONE){
				newcell.goal = true;
			}
			else newcell.goal = false;
			if (j != 14) {
				check_south(newcell, j, i);
			}
			if (i != 14) {
				check_east(newcell, j, i);
			}
			if (i != 0) {
				check_west(newcell, j, i);
			}	
			if (j != 0) {
				check_north(newcell, j, i);
			}
			game[j / 2][i / 2] = newcell;
		}
	}
}
// check_north.
// Parameters: address of Cell, and row and col of its location in array
// Returns: Nothing
// Does: fills north boolean in cell struct
void Board::check_north(Cell &i, int row, int col)
{
	if (preGame[row - 1][col] == HOR) {
		i.north = false;
	} 
	else i.north = true;
}
// check_south
// Parameters: address of Cell, and row and col of its location in array
// Returns: Nothing
// Does: fills south boolean in cell struct
void Board::check_south(Cell &i, int row, int col)
{
	if (preGame[row + 1][col] == HOR) {
		i.south = false;
	} 
	else i.south = true;
}
// check_east
// Parameters: address of Cell, and row and col of its location in array
// Returns: Nothing
// Does: fills east boolean in cell struct
void Board::check_east(Cell &i, int row, int col)
{
	if (preGame[row][col + 1] == VER) {
		i.east = false;
	} 
	else i.east = true;	
}
// check_west
// Parameters: address of Cell, and row and col of its location in array
// Returns: Nothing
// Does: fills west boolean in cell struct
void Board::check_west(Cell &i, int row, int col)
{
	if (preGame[row][col - 1] == VER) {
		i.west = false;
	} 
	else i.west = true;	
}


// print_board
// Parameters: None.
// Returns: Nothing.
// Does: prints the final game board to cout
void Board::print_board()
{
	for (int j = 0; j < LEN; j++) {
		for (int i = 0; i < WID; i++) {
			cout << game[j][i].symbol;
			if (!game[j][i].east && i != WID - 1) {
				cout << VER;
			}
			else if (i != WID -1) {
				cout << " ";
			}
			if (i == WID - 1) {
				cout << endl;
				if (j == LEN - 1) {
					cout << endl;
					return;
				}
				for (int s = 0; s < LEN * 2 - 1; s++) {
					if (preGame[j * 2 + 1][s] == HOR) {
						cout << preGame[j * 2 + 1][s];
					}
					else cout << " ";
				}
				cout << endl;
			}
		}
	}
}
// cell_at
// Parameters: robot row and col
// Returns: cell where robot is
// Does: returns robot's current cell
Cell* Board::cell_at(int rrow, int rcol)
{
	return &game[rrow - 1][rcol - 1];
}
// is_over
// Parameters: None
// Returns: true if game is over and false if not
// Does: Sees if user has won yet or not
bool Board::is_over()
{
	if (!winner) {
		return false;
	}
	return true;
}
// add_robot
// Parameters: robot's symbol and its row and col
// Returns: nothing
// Does: adds the robot symbol to specified position
void Board::add_robot(char sym, int row, int col)
{
	game[row - 1][col - 1].symbol = sym;
	rSymbol = sym;
	robo_row = row;
	robo_col = col;
}
// update_robot
// Parameters: None
// Returns: Nothing
// Does: updates correct symbol with the robot and sees if it's the winning 
// symbol.
void Board::update_robot()
{
	if (game[robo_row - 1][robo_col - 1].goal) {
		winner = true;
	}
	game[robo_row - 1][robo_col - 1].symbol = rSymbol;
}
// move_down
// Parameters: None
// Returns: Nothing
// Does: Uses recursion to move the robot down until it can't move.
void Board::move_down()
{
	if (!game[robo_row - 1][robo_col - 1].south) {
		update_robot();
		return;
	}
	robo_row++;
	move_down();
}
// move_left
// Parameters: None
// Returns: Nothing
// Does: Uses recursion to move the robot left until it can't move.
void Board::move_left()
{
	if (!game[robo_row - 1][robo_col - 1].west) {
		update_robot();
		return;
	}
	robo_col--;
	move_left();
}
// move_right
// Parameters: None
// Returns: Nothing
// Does: Uses recursion to move the robot right until it can't move.
void Board::move_right()
{
	if (!game[robo_row - 1][robo_col - 1].east) {
		update_robot();
		return;
	}
	robo_col++;
	move_right();
}

// move_up
// Parameters: None
// Returns: Nothing
// Does: Uses recursion to move the robot up until it can't move.
void Board::move_up()
{
	if (!game[robo_row - 1][robo_col - 1].north) {
		update_robot();
		return;
	}
	robo_row--;
	move_up();
}
// remove_robot
// Parameters: None
// Returns: Nothing
// Does: Updates robot's old cell back to open symbol
void Board::remove_robot()
{
	game[robo_row - 1][robo_col - 1].symbol = OPEN;
}
// get_robo_row
// Parameters: None
// Returns: Int of robot's row
// Does: returns the current row of the robot
int Board::get_robo_row()
{
	return robo_row ;
}
// get_robo_col
// Parameters: None
// Returns: int of robots col
// Does: Returns the current col of the robot.
int Board::get_robo_col()
{
	return robo_col;
}
// manual_move_robot
// Parameters: desired row and col ints
// Returns: nothing
// Does: updates robot to a specified pos.
void Board::manual_move_robot(int row, int col)
{
	remove_robot();
	robo_row = row;
	robo_col = col;
	update_robot();
}






