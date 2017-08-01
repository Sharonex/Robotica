#include "MovementManager.h"

#include <iostream>

using namespace std;
const float speed=0.3;

MovementManager::MovementManager(Hamster *hamster) :hamster(hamster) {
}
void MovementManager::StartMovement(HamsterAPI::LidarScan scan){
	this->ObstacleAvoidance(scan);
}

void MovementManager::ObstacleAvoidance(HamsterAPI::LidarScan scan) {
	cout << "Distance from obstacle in front: " << scan.getDistance(180) << endl;

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

MovementManager::~MovementManager() {
}
