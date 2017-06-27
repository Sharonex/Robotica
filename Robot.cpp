/*
 * Robot.cpp
 *
 *  Created on: Jan 12, 2017
 *      Author: user
 */

#include "Robot.h"
#include "LocalizationManager.h"


using namespace robotics;
using namespace HamsterAPI;
using namespace manager;


Robot::Robot() {
	// TODO Auto-generated constructor stub
	this->hamster = new HamsterAPI::Hamster(1);
	this->rand_walk = RandomWalk(this->hamster);
	map = NULL;
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
	if(map != NULL)
		delete map;
	if( hamster!= NULL)
		delete hamster;
}

void Robot::start()
{
	srand(time(NULL));//for random walk
	try {
		int flag = 1;
		LocalizationManager* manager;
		while (this->hamster->isConnected())//loop for getting the Slam Map
		{
			try {
					while(flag==1)
					{
						try {
							ogrid = this->hamster->getSLAMMap();
							cout<<1<<endl;
							flag = 0;
						} catch(const HamsterAPI::HamsterError & message_error){
						  flag = 1;
						}
					}

					map = new Map(ogrid);
					manager = new LocalizationManager(ogrid);
					break;
					} catch (const HamsterAPI::HamsterError & message_error) {
						HamsterAPI::Log::i("Client", message_error.what());
					}
		}
		while (this->hamster->isConnected()) //MAIN loop
		{
			try {
				/*if(flag == 0)
				{
					map->drawMap(manager->getParticles());
					flag = 1;
				}*/
				//updateParticles - add parameter lidarScan
				HamsterAPI::LidarScan scan = this->hamster->getLidarScan();
				//manager->updateParticles(scan);
				//cout<<"done with update"<<endl;
				//cout<<"original size "<<manager->getParticles().size()<<endl;
				//map->drawMap(&manager->getParticles());
				//cout<<"done with drawing"<<endl;
				this->rand_walk.walk(scan);
				//this->rand_walk.turnLeft();
				//cout<<"done with walking"<<endl;
				//cout<<"end of loop"<<endl;

			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}

		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
	delete map;


}

