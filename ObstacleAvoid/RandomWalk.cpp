/*
 * RandomWalk.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: user
 */

#include "RandomWalk.h"
#include <iostream>

using namespace std;
const float speed=0.3;

RandomWalk::RandomWalk(Hamster *hamster) :hamster(hamster) {
}
void RandomWalk::StartRandomWalk(HamsterAPI::LidarScan scan){
	this->ObstacleAvoidance(scan);
}

void RandomWalk::ObstacleAvoidance(HamsterAPI::LidarScan scan) {
	//cout << "Distance from obstacle in front: " << scan.getDistance(180) << endl;

	bool isObstacleInFront = false;

	for (int i = 150; i <= 210; i++) {
		if (scan.getDistance(i) < 0.8) {
			isObstacleInFront = true;
			break;
		}
	}

	if (isObstacleInFront)
		hamster->sendSpeed(0.4, 45);
	else
		hamster->sendSpeed(0.4, 0.0);
}



RandomWalk::~RandomWalk() {
	// TODO Auto-generated destructor stub
}
