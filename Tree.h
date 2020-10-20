/* Jack Burns
 * Comp 15
 * 16 October, 2019
 * Tree.h
 */

#include "Board.h"

using namespace std;

#ifndef _TREE_H_
#define _TREE_H_

const int MAX_MOVES = 7;
const char FINISH = '*';

struct TreeNode {
	TreeNode *north;
	TreeNode *south;
	TreeNode *east;
	TreeNode *west;
	Cell *info;
};

struct Route {
	bool found;
	vector < char > moves;
};
class Tree
{
public:
	Tree();
	~Tree();
	void destroy_tree(TreeNode *p);

	void create_list(Board &game, int row, int col);
	TreeNode *add_north(Board &game, int row, int col, TreeNode *p, int count);
	TreeNode *add_south(Board &game, int row, int col, TreeNode *p, int count);
	TreeNode *add_east(Board &game, int row, int col, TreeNode *p, int count);
	TreeNode *add_west(Board &game, int row, int col, TreeNode *p, int count);

	void print_tree();

	void search_tree();
	void search_tree_help(TreeNode *root, int count, int &theCount);
	void print_path(int &theCount);

private:

	TreeNode *parent;
	Route *theRoute;
	int numMoves;

};

#endif

