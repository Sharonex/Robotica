/*
 * LocalizationManager.h
 *
 *  Created on: Jan 12, 2017
 *      Author: user
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#define NUM_OF_PARTICLES 100///////////////////////////////////////////////////////////////////////////////////////////////////////////
#define HIGH_BELEIF 0.75
#define LOW_BELEIF 0.05

#include "Particle.h"
#include <vector>
#include <HamsterAPIClientCPP/Hamster.h>

using namespace std;
using namespace HamsterAPI;

namespace manager
{
class LocalizationManager
{
private:
	vector<Particle *> particles;
	const OccupancyGrid &ogrid;
	void getRandomLocation(Particle* par);
	HamsterAPI::LidarScan scan;
public:
	LocalizationManager(const OccupancyGrid &ogrid);
	void initParticles();
	void updateParticles(HamsterAPI::LidarScan scan);
	virtual ~LocalizationManager();
	void createNewParticles(Particle* par, vector<Particle *>* newParticles);
	const vector<Particle*>& getParticles() const
	{
		return particles;
	}
};
}

#endif /* LOCALIZATIONMANAGER_H_ */
