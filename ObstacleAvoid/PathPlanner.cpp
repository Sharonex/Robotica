/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 23, 2017
 *      Author: user
 */

#include "PathPlanner.h"

PathPlanner::PathPlanner(OccupancyGrid &grid, int startRow, int startCol) :
grid(grid),
startRow(startRow),
startCol(startCol) {
}

void PathPlanner::buildGraph() {
	int rows = grid.getHeight();
	int cols = grid.getWidth();

	mat.resize(rows);

	for (int i = 0; i < rows; i++) {
		mat[i].resize(cols);

		for (int j = 0; j < cols; j++) {
			Cell c = grid.getCell(i, j);
			if (c == CELL_FREE) {
				Node *node = new Node();
				node->row = i;
				node->col = j;
				node->f = 0;
				mat[i][j] = node;
			}
		}
	}
}

struct NodeComparer {
	bool operator() (const Node *n1, const Node *n2) const {
		return n1->f < n2->f;
	}
};

vector<Node *> PathPlanner::getSuccessors(Node *node) {
	uint row = node->row;
	uint col = node->col;

	vector<Node *> successors;

	if (row < grid.getHeight() && mat[row + 1][col]) {
		successors.push_back(mat[row + 1][col]);
	}

	if (row > 0 && mat[row - 1][col]) {
			successors.push_back(mat[row - 1][col]);
	}

	if (col < grid.getWidth() && mat[row][col + 1]) {
			successors.push_back(mat[row][col + 1]);
	}

	if (col < 0 && mat[row][col - 1]) {
			successors.push_back(mat[row][col - 1]);
	}

	return successors;
}

float PathPlanner::getEstimatedDistance(Node *successor, Node *goal) {
	return fabsf(successor->row - goal->row) + fabsf(successor->col - goal->col);
};

Path* PathPlanner::computeShortestPath(Node *goal) {
	buildGraph();

	Path* path = new Path();

	Node *startNode = mat[startRow][startCol];
	startNode->g = 0;
	startNode->h = getEstimatedDistance(startNode, goal);
	startNode->f = startNode->g + startNode->h;
	startNode->parent = 0;

	priority_queue<Node *, vector<Node *>, NodeComparer> openList;
	openList.push(startNode);

	while (!openList.empty()) {
		Node *currNode = openList.top();
		openList.pop();
		vector<Node *> successors = getSuccessors(currNode);

		for (uint k = 0; k < successors.size(); k++) {
			Node *successor = successors[k];
			successor->parent = currNode;

			if (successor->row == goal->row && successor->col == goal->col) {

				goal->parent = successor->parent;
				goal->g = successor->g;

				// ????
				// add to path and return
				pair<int, int> pair(successor->row,successor->col);
				path->push_back(pair);

				return path;
				// lmao idk how to cpp wtf is pointers
			}

			successor->g = currNode->g + 1;
			successor->h = getEstimatedDistance(successor, goal);
			successor->f = successor->g + successor->h;
		}
	}

	return path;
}

PathPlanner::~PathPlanner() {

}
