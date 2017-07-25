/*
 * main.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: user
 */

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include "Robot.h"
#include "LocalizationManager.h"
#include "Map.h"
#include "RandomWalk.h"

using namespace std;
using namespace HamsterAPI;
HamsterAPI::Hamster * hamster;

int main() {
	try {
		hamster = new HamsterAPI::Hamster(1);
		sleep(1);

		OccupancyGrid ogrid = hamster->getSLAMMap();
		Map map(ogrid);
		map.initMap();
		Robot robot(hamster);
		LocalizationManager locManager(ogrid, hamster);
		locManager.initParticles();
		RandomWalk randomWalk(hamster);
		HamsterAPI::LidarScan ld;

		while (hamster->isConnected()) {
			try {
				map.showMap();
				ld = hamster->getLidarScan();
				robot.updatePose();
				locManager.updateParticles(robot.getDeltaX(), robot.getDeltaY(), robot.getDeltaYaw(),ld);
				locManager.evolveParticles();
				randomWalk.StartRandomWalk(ld);
				map.drawParticles(locManager.getParticles());

				sleep(0.5);

			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}

		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
	return 0;
}

