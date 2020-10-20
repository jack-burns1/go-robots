/* Jack Burns
 * Comp 15
 * 14 October, 2019
 * main.cpp
 */

#include "Board.h"
#include "Tree.h"

using namespace std;

const char UP = 'w';
const char DOWN = 's';
const char LEFT = 'a';
const char RIGHT = 'd';
const char QUIT = 'q';

void run_correct_mode(Board &theGame, int row, int col, string mode);
void run_with_tree(Board &theGame, int r, int c);
void run_with_interactive(Board &theGame);
void move_up(Board &theGame, char move);
void move_down(Board &theGame, char move);
void move_left(Board &theGame, char move);
void move_right(Board &theGame, char move);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cout << "Wrong number of commands\n";
		return 0;
	}
	cout << "Welcome to Ricocheting Robots!";
	cout << endl;
	char symbol;
	int row;
	int col;
	string mode;
	cout << "Enter Robot symbol (1 Char): ";
	cin >> symbol;
	cout << "Enter starting row: ";
	cin >> row;
	cout << "Enter starting col: ";
	cin >> col;
	cout << "Please enter AUTO for automatic solver and INTER for an";
	cout << " interactive game mode!\n";
	cin >> mode;

	string filename = argv[1];
	Board theGame;
	theGame.read_in_board(filename);
	theGame.add_robot(symbol, row, col);
	run_correct_mode(theGame, row, col, mode);
	return 0;
}
// run_correct_mode
// Parameters: instance of game, robot's starting position, and user specified
// mode
// Returns: Nothing
// Purpose: Direct the program based on user input
void run_correct_mode(Board &theGame, int row, int col, string mode)
{
	if (mode == "AUTO") {
		run_with_tree(theGame, row, col);
	}
	else if (mode == "INTER") {
		cout << endl;
		theGame.print_board();
		run_with_interactive(theGame);
	}
	else return;
}
// run_with_tree
// Parameters: game board, and staring row and col
// Returns: nothing
// Purpose: run the program with a tree and and find the route
void run_with_tree(Board &theGame, int r, int c)
{
	Tree pine;
	pine.create_list(theGame, r, c);
	pine.search_tree();
}
// run_with_interactive
// Parametes: game board
// Returns: Nothing
// Purpose: directs main based on continued user input
void run_with_interactive(Board &theGame)
{
	char move;
	bool you_win = false;
	while (!you_win) {
		cin >> move;
		if (move == UP) {
			move_up(theGame, move);
		}
		else if (move == DOWN) {
			move_down(theGame, move);
		}
		else if (move == LEFT) {
			move_left(theGame, move);
		}
		else if (move == RIGHT) {
			move_right(theGame, move);
		}
		else if (move == QUIT) {
			cout << "move: " << move;
			cout << "Quitting...\n";
			return;
		}
		else cout << "INVALID MOVE\n";

		cout << endl;
		you_win = theGame.is_over();
	}
	cout << "Congratulations!! You Win!!!!\n";
}
// move_up
// Parametes: game board, and user char input
// Returns:  Nothing
// Purpose: Call functions to move the robot north
void move_up(Board &theGame, char move)
{
	cout << "move: " << move << " -> moving north\n";
	cout << endl;
	theGame.remove_robot();
	theGame.move_up();
	theGame.print_board();
}
// move_down
// Parametes: game board, and user char input
// Returns: Nothing
// Purpose:  Call functions to move robot south
void move_down(Board &theGame, char move)
{
	cout << "move: " << move << " -> moving south\n";
	cout << endl;
	theGame.remove_robot();
	theGame.move_down();
	theGame.print_board();
}
// move_left
// Parametes: game board, and user char input
// Returns: Nothing
// Purpose: Call functions to move robot west
void move_left(Board &theGame, char move)
{
	cout << "move: " << move << " -> moving west\n";
	cout << endl;
	theGame.remove_robot();
	theGame.move_left();
	theGame.print_board();
}
// move_right
// Parametes: game board, and user char input
// Returns: Nothing
// Purpose: Call functions to move robot east
void move_right(Board &theGame, char move)
{
	cout << "move: " << move << " -> moving east\n";
	cout << endl;
	theGame.remove_robot();
	theGame.move_right();
	theGame.print_board();
}











