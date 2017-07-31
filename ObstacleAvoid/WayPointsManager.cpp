/*
 * WaypointsManager.cpp
 *
 *  Created on: Jul 13, 2017
 *      Author: user
 */

#include "WayPointsManager.h"

WaypointsManager::WaypointsManager(OccupancyGrid* grid) {
	m_coarseGrid = grid;
}

WaypointsManager::~WaypointsManager() {
}

bool WaypointsManager::raytraceWillCollide(cv::Point2i start, cv::Point2i end)
{
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    int x = start.x;
    int y = start.y;
    int n = 1 + dx + dy;
    int x_inc = (end.x > start.x) ? 1 : -1;
    int y_inc = (end.y > start.y) ? 1 : -1;
    int error = dx - dy;
    dx *= 2;
    dy *= 2;

    for (; n > 0; --n)
    {
    	// Check if it collides with something
    	if(m_coarseGrid->getCell(x,y) != CELL_FREE)
    	{
    		return true;
    	}

    	// Continue raytrace
        if (error > 0)
        {
            x += x_inc;
            error -= dy;
        }
        else
        {
            y += y_inc;
            error += dx;
        }
    }

    return false;
}

int WaypointsManager::getNextWaypoint(Path* path, int startNodeIndex) {
	int nextWaypoint = -1;
	Node* targetNode;
	Node* startNode = (*path)[startNodeIndex];
	cv::Point2i start(startNode->col,startNode->row);
	int max_nodes_ahead = std::min(MAX_NODES_WAYPOINT,(int)path->size() - startNodeIndex - 1);

	for (int nodesAhead = max_nodes_ahead;nodesAhead > 0;--nodesAhead)
	{
		int targetNodeIndex = startNodeIndex + nodesAhead;

		targetNode = (*path)[startNodeIndex + targetNodeIndex];
		cv::Point2i end(targetNode->col,targetNode->row);

		if(!raytraceWillCollide(start,end))
		{
			// Set waypoint to next node, we know its ok
			nextWaypoint = targetNodeIndex;
			break;
		}
	}

	return nextWaypoint;
}

list<cv::Point2i> WaypointsManager::computeWaypoints(Path* path) {
	int startNodeIndex = 0;
	list<cv::Point2i> waypoints;
	bool isDone = false;
	int pathGoalIndex = ((int)path->size() - 1);

	do {
		int nextWaypointIndex = getNextWaypoint(path,startNodeIndex);

		if (-1 == nextWaypointIndex)
		{
			cout << "[ERROR] getNextWaypoint did not find a next waypoint (start = " << startNodeIndex << ")" << endl;
			waypoints.clear();
			return waypoints;
		}
		else
		{
			Node* nextWaypoint = (*path)[nextWaypointIndex];
			waypoints.push_back(cv::Point2i(nextWaypoint->col,nextWaypoint->row));
			startNodeIndex = nextWaypointIndex;

			if (pathGoalIndex == nextWaypointIndex)
				isDone = true;
		}
	}
	while(!isDone);

	return waypoints;
}
