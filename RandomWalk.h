/*
 * RandomWalk.h
 *
 *  Created on: Jan 12, 2017
 *      Author: user
 */

//#include "Walk.h"
#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#ifndef RANDOMWALK_H_
#define RANDOMWALK_H_

namespace robotics{
class RandomWalk{
private:
	HamsterAPI::Hamster * hamster;
	HamsterAPI::LidarScan scan;
	bool moveBack;
	bool moveLeft;
	bool moveRight;
public:
	RandomWalk();
	RandomWalk(HamsterAPI::Hamster * hamster);
	virtual void walk(HamsterAPI::LidarScan scan);
	virtual ~RandomWalk();
	bool isFrontFree();
	bool isLeftFree();
	bool isRightFree();
	bool isBackFree();
	void moveForward();
	void turnLeft();
	void turnRight();
	void moveBackwards();
	void stopMoving();
	void turning();
	void getScansBetween(double min, double max, std::vector<double> & distances);
	double CalcMHWScore(vector<double> scores);
	bool willCollide(std::vector<double> distances, int angle_from_center);
	void moveLeftBack();
	void moveRightBack();
};
}

#endif /* RANDOMWALK_H_ */
