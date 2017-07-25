/*
 * PathPlanner.h
 *
 *  Created on: Jun 23, 2017
 *      Author: user
 */

#ifndef SRC_PATHPLANNER_H_
#define SRC_PATHPLANNER_H_

#include <HamsterAPIClientCPP/Hamster.h>
#include <vector>
#include <queue>
#include "Node.h"

using namespace HamsterAPI;
using namespace std;

typedef vector<pair<int, int> > Path;

class PathPlanner {
private:
	OccupancyGrid &grid;
	int startRow, startCol;
	vector<vector<Node*> > mat;

	void buildGraph();
	vector<Node *> getSuccessors(Node *node);
	float getEstimatedDistance(Node *successor, Node *goal);

public:
	PathPlanner(OccupancyGrid &grid, int startRow, int startCol);
	Path* computeShortestPath(Node *goal);
	virtual ~PathPlanner();
};

#endif /* SRC_PATHPLANNER_H_ */
