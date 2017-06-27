/*
 * Particle.h
 *
 *  Created on: Jan 12, 2017
 *      Author: user
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>

using namespace HamsterAPI;
using namespace std;

class Particle
{
public:
	float x;
	float y;
	float teta;
private:
	float belief;
public:
	Particle();
	Particle(float x, float y, float teta);
	float update(HamsterAPI::LidarScan scan, const OccupancyGrid& ogrid);/*float x,float y,float teta,float belief*/
	Particle* createParticle(int right_left_X, int up_down_Y);
	float getBelief();
	bool operator!=(const Particle p) const;
	virtual ~Particle();
	void print();
};

#endif /* PARTICLE_H_ */
