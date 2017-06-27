/*
 * Robot.h
 *
 *  Created on: Jan 12, 2017
 *      Author: user
 */

#include "RandomWalk.h"
#include <HamsterAPIClientCPP/Hamster.h>
#include "LocalizationManager.h"
#include "Map.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

#ifndef ROBOT_H_
#define ROBOT_H_

using namespace robotics;


class Robot {
private:
	HamsterAPI::Hamster * hamster;
	RandomWalk rand_walk;
	Map *map;
	OccupancyGrid ogrid;
	//HamsterAPI::LidarScan scan;
public:
	Robot();
	void start();
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
