/*
 * RandomWalk.h
 *
 *  Created on: Mar 5, 2017
 *      Author: user
 */

#ifndef RANDOMWALK_H_
#define RANDOMWALK_H_

#include "Particle.h"
#include <vector>
#include <HamsterAPIClientCPP/Hamster.h>

using namespace std;
using namespace HamsterAPI;

class RandomWalk {
private:
	Hamster *hamster;
	void ObstacleAvoidance(HamsterAPI::LidarScan scan);

public:
	RandomWalk(Hamster *hamster);
	void StartRandomWalk(HamsterAPI::LidarScan scan);

	virtual ~RandomWalk();
};




#endif /* RANDOMWALK_H_ */
