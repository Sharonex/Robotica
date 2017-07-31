/*
 * RobotMovement.h
 *
 *  Created on: Jul 26, 2017
 *      Author: user
 */

#ifndef ROBOTMOVEMENT_H_
#define ROBOTMOVEMENT_H_

#include "Map.h"
#include <math.h>
#include <HamsterAPIClientCPP/Hamster.h>

using HamsterAPI::OccupancyGrid;
using namespace HamsterAPI;

using namespace std;

class RobotMovement {
private:
	const float RANGE_BUFFER;
	Map * _map;
	void PrintRobotLocation(HamsterAPI::Hamster * hamster);
	float CalculateAngleForMovemant(Pose * currentPosition, Pose * targetPosition);
	float NormalizeAngle(float angle);
	bool CheckIfArrive(Pose * currentPosition, Pose * targetPosition);

public:
	RobotMovement(Map * map);
	virtual ~RobotMovement();
	void MoveRobotToWaypoint(HamsterAPI::Hamster * hamster, Pose * positionTarget);
};

#endif /* ROBOTMOVEMENT_H_ */
