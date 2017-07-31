/*
 * main.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: user
 */
#include <string>

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include "Robot.h"
#include "LocalizationManager.h"
#include "Map.h"
#include "RandomWalk.h"
#include "ConfigurationManager.h"
#include "PathPlanner.h"
#include "RobotMovement.h"

using namespace std;
using namespace HamsterAPI;
HamsterAPI::Hamster * hamster;

int main() {
	try {
		hamster = new HamsterAPI::Hamster(1);
		sleep(3);
		ConfigurationManager::Init(string("parameters.txt"));
		OccupancyGrid ogrid = hamster->getSLAMMap();
		Map map(ogrid);
		map.initMap();
		Robot robot(hamster);
		LocalizationManager locManager(ogrid, hamster);
		locManager.initParticles();

		cv::Point2f target = ConfigurationManager::getTargetPoint();
		Pose start_pos = ConfigurationManager::getStartPose();

		PathPlanner pp(ogrid, start_pos.x_, start_pos.y_);
		HamsterAPI::LidarScan ld;

		Path* path = pp.getPath(target);

		if (path->empty())
		{
			cout << "No path found from " << start_pos.y_ << "," << start_pos.x_ << ") to (" << target.x << "," << target.y << ")" << endl;
		}

		// Waypoint
		WaypointsManager* waypointManager = new WaypointsManager(ogrid);
		list<cv::Point2i> waypoints = waypointManager->computeWaypoints(path);
		list<cv::Point2i>::iterator iter = waypoints.begin();

		RobotMovement rm(map);

		while (hamster->isConnected() && iter != waypoints.end()) {
			try {
				map.showMap();
				ld = hamster->getLidarScan();
				robot.updatePose();
				locManager.evolveParticles();
				locManager.updateParticles(robot.getDeltaX(), robot.getDeltaY(), robot.getDeltaYaw(),ld);
				map.drawParticles(locManager.getParticles());
				sleep(0.3);

				Pose next_pos(iter->x, iter->y, 0);
				rm.MoveRobotToWaypoint(hamster, &next_pos);
				iter++;
			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}
		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}

	ConfigurationManager::Destroy();
	return 0;
}

