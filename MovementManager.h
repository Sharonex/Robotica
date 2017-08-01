#ifndef MOVEMENTMANAGER_H_
#define MOVEMENTMANAGER_H_

#include "Particle.h"
#include <vector>
#include <HamsterAPIClientCPP/Hamster.h>

using namespace std;
using namespace HamsterAPI;

class MovementManager {
private:
	Hamster *hamster;
	void ObstacleAvoidance(HamsterAPI::LidarScan scan);

public:
	MovementManager(Hamster *hamster);
	void StartMovement(HamsterAPI::LidarScan scan);

	virtual ~MovementManager();
};




#endif /* MOVEMENTMANAGER_H_ */
