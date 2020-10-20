/* Jack Burns
 * Comp 15
 * 14 October, 2019
 * Tree.cpp
 */

#include "Tree.h"


Tree::Tree()
{
	numMoves = 0;

	parent = new TreeNode;
	parent->north = NULL;
	parent->south = NULL;
	parent->east = NULL;
	parent->west = NULL;
	parent->info = NULL;

	theRoute = new Route;
	theRoute->found = false;		
}
Tree::~Tree()
{
	destroy_tree(parent);
	delete theRoute;
}
// destroy_tree
// Parameters: TreeNode of a parent
// Returns: Nothing.
// Purpose: Find all of the leaves and delete the tree from leaves up to the
// root.
void Tree::destroy_tree(TreeNode *p)
{
	if (p == NULL) {
		delete p;
		return;
	}
	if (p->north == NULL && p->south == NULL && p->east == NULL &&
		p->west == NULL) {
		delete p;
		return;
	}
	else {
		destroy_tree(p->north);
		destroy_tree(p->south);
		destroy_tree(p->east);
		destroy_tree(p->west);
		delete p;
	}
}
// create_list
// Parameters: instance of the game board, and the robot's starting row and col
// Returns: Nothing.
// Purpose: Call appropriate functions to create tree of robot's moves
void Tree::create_list(Board &game, int row, int col)
{
	parent->info = game.cell_at(row, col);
	parent->north = add_north(game, row, col, parent, 0);
	game.manual_move_robot(row, col);
	parent->south = add_south(game, row, col, parent, 0);
	game.manual_move_robot(row, col);
	parent->east = add_east(game, row, col, parent, 0);	
	game.manual_move_robot(row, col);
	parent->west = add_west(game, row, col, parent, 0);

}
// add_north
// Parameters: Instance of game board, current robot row and col, the parent 
// TreeNode whose children it's creating and a counter.
// Returns: A new treeNode of the parent's north child.
// Purpose: to check and add the north direction to a treeNode, and then add
// children to that through recusion
TreeNode *Tree::add_north(Board &game, int row, int col, TreeNode *p, int count)
{
	p->north = new TreeNode;
	p->north->info = NULL;
	p->north->north = NULL;
	p->north->south = NULL;
	p->north->east = NULL;
	p->north->west = NULL;
	if (p->info->north && count <= MAX_MOVES) {
		game.remove_robot();
		game.move_up();
		row = game.get_robo_row();
		col = game.get_robo_col();
		p->north->info = game.cell_at(row, col);
		count++;
		p->north->east = add_east(game, row, col, p->north, count);
		p->north->west = add_west(game, row, col, p->north, count);
		return p->north;
	}
	else delete p->north;
	return NULL;
}
// add_south
// Parameters: Instance of game board, current robot row and col, the parent 
// TreeNode whose children it's creating and a counter.
// Returns: A new treeNode of the parent's south child.
// Purpose: to check and add the south direction to a treeNode, and then add
// children to that through recusion
TreeNode *Tree::add_south(Board &game, int row, int col, TreeNode *p, int count)
{
	p->south = new TreeNode;
	p->south->info = NULL;
	p->south->south = NULL;
	p->south->north = NULL;
	p->south->east = NULL;
	p->south->west = NULL;
	if (p->info->south && count <= MAX_MOVES) {
		game.remove_robot();
		game.move_down();
		row = game.get_robo_row();
		col = game.get_robo_col();
		p->south->info = game.cell_at(row, col);
		count++;
		p->south->east = add_east(game, row, col, p->south, count);
		p->south->west = add_west(game, row, col, p->south, count);
		return p->south;
	}
	else delete p->south;
	return NULL;
}
// add_east
// Parameters:Instance of game board, current robot row and col, the parent 
// TreeNode whose children it's creating and a counter.
// Returns: A new treeNode of the parent's east child.
// Purpose: to check and add the east direction to a treeNode, and then add
// children to that through recusion
TreeNode *Tree::add_east(Board &game, int row, int col, TreeNode *p, int count)
{
	p->east = new TreeNode;
	p->east->info = NULL;
	p->east->east = NULL;
	p->east->west = NULL;
	p->east->north = NULL;
	p->east->south = NULL;
	if (p->info->east && count <= MAX_MOVES) {
		game.remove_robot();
		game.move_right();
		row = game.get_robo_row();
		col = game.get_robo_col();
		p->east->info = game.cell_at(row, col);
		count++;
		p->east->north = add_north(game, row, col, p->east, count);
		p->east->south = add_south(game, row, col, p->east, count);
		return p->east;
	}
	else delete p->east;
	return NULL;
}
// add_west
// Parameters: Instance of game board, current robot row and col, the parent 
// TreeNode whose children it's creating and a counter.
// Returns: A new treeNode of the parent's west child.
// Purpose: to check and add the west direction to a treeNode, and then add
// children to that through recusion
TreeNode *Tree::add_west(Board &game, int row, int col, TreeNode *p, int count)
{
	p->west = new TreeNode;
	p->west->info = NULL;
	p->west->west = NULL;
	p->west->east = NULL;
	p->west->north = NULL;
	p->west->south = NULL;
	if (p->info->west && count <= MAX_MOVES) {
		game.remove_robot();
		game.move_left();
		row = game.get_robo_row();
		col = game.get_robo_col();
		p->west->info = game.cell_at(row, col);
		count++;
		p->west->north = add_north(game, row, col, p->west, count);
		p->west->south = add_south(game, row, col, p->west, count);
		return p->west;
	}
	else delete p->west;
	return NULL;
}
// print_tree
// Parameters: None.
// Returns: Nothing.
// Purpose: prints parent and its children's board symbol to cout for debugging
void Tree::print_tree()
{
	cout << parent->info->symbol << "parent\n";
	cout << parent->north->info->symbol << "n\n";
	cout << parent->south->info->symbol << "s\n";
	cout << parent->east->info->symbol << "e\n";
	cout << parent->west->info->symbol << "w\n";
}
// search_tree
// Parameters: None
// Returns: Nothing.
// Purpose: Calls helper functions to find correct path in tree
void Tree::search_tree()
{
	int theCount = 8;
	search_tree_help(parent, 0, theCount);
	print_path(theCount);
}
// search_tree_help
// Parameters: parent of directions it searches, current move count, and count
// of the least amount of moves currently possible
// Returns: Nothing.
// Purpose: iterate through the tree and fill a vector of roots
void Tree::search_tree_help(TreeNode *root, int count, int &theCount)
{
	if (root->info->goal) {
		theRoute->found = true;
		theCount = count;
		theRoute->moves.push_back(FINISH);
		return;
	}
	if (root == NULL) {
		return;
	}
	while (!theRoute->found || count < theCount) {
		count++;
		if (root->north != NULL) {
			theRoute->moves.push_back('N');
			search_tree_help(root->north, count, theCount);
		}
		if (root->south != NULL) {
			theRoute->moves.push_back('S');
			search_tree_help(root->south, count, theCount);
		}
		if (root->east != NULL) {
			theRoute->moves.push_back('E');
			search_tree_help(root->east, count, theCount);
		}
		if (root->west != NULL) {
			theRoute->moves.push_back('W');
			search_tree_help(root->west, count, theCount);
		}
		return;
	}
}
// print_path
// Parameters: Smallest number of moves it takes to finish
// Returns: Nothing.
// Purpose: to print out the correct chars of the solution
void Tree::print_path(int &theCount)
{
	if (theCount == 8) {
		cout << "No solution\n";
		return;
	}
	int i = 0;
	i = theRoute->moves.size() - 1;
	while (theRoute->moves.at(i) != FINISH) {
		i--;
	}
	for (int j = theCount; j > 0; j--) {
		cout << theRoute->moves[i - j] << " -> ";
	}
	cout << "Found the target!\n";
}









