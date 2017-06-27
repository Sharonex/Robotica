/*
 * Map.h
 *
 *  Created on: Jan 16, 2017
 *      Author: user
 */

#ifndef MAP_H_
#define MAP_H_

#include <HamsterAPIClientCPP/Hamster.h>
#include "Particle.h"

using namespace std;
using namespace HamsterAPI;
using namespace cv;

class Map {
private:
	//const OccupancyGrid ogrid;
	const OccupancyGrid &ogrid;
public:
	Map(const OccupancyGrid& ogrid);
	void drawMap(const vector<Particle*> *particles);
	virtual ~Map();
};

#endif /* MAP_H_ */
