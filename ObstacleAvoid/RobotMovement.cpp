/*
 * RobotMovement.cpp
 *
 *  Created on: Jul 26, 2017
 *      Author: user
 */

#include "RobotMovement.h"
#include <math.h>

RobotMovement::RobotMovement(Map * map) : RANGE_BUFFER(0.3),_map(map){
}

RobotMovement::~RobotMovement() {
}


// Return true if arrive to target and false if not
void RobotMovement::MoveRobotToWaypoint(HamsterAPI::Hamster * hamster, Pose * positionTarget)
{
	try {
			sleep(0.3);
			Pose currentLocation = hamster->getPose();
			if(CheckIfArrive(&currentLocation, positionTarget))
			{
				cout << "RETURN TRUE HERE!!!!!" << endl << endl << endl;
				return;
			}
			HamsterAPI::LidarScan ld = hamster->getLidarScan();

			// Robot near obstacle - go back
			if (ld.getDistance(180) < 0.4) {
				hamster->sendSpeed(-0.5, -10);
				cout << "Front: " << ld.getDistance(180) << endl;
			}
			// Robot near obstacle - go right / left
			else if (ld.getDistance(180) < 0.8) {
				if(ld.getDistance(90) < ld.getDistance(270))
				{
					// Turn right
					hamster->sendSpeed(0.5, 45);
				}
				else
				{
					// Turn left
					hamster->sendSpeed(0.5, -45);
				}
				cout << "Front: " << ld.getDistance(180) << endl;
			}
			// Move
			else
			{

				float angle = CalculateAngleForMovemant(&currentLocation, positionTarget);

				sleep(0.2);
				hamster->sendSpeed(1.0, angle);

			}

			// Print Location
			PrintRobotLocation(hamster);

		} catch (const HamsterAPI::HamsterError & message_error) {
			HamsterAPI::Log::i("Client", message_error.what());
		}
}

void RobotMovement::PrintRobotLocation(HamsterAPI::Hamster * hamster){
	Pose currentLocation = hamster->getPose();
	cout << currentLocation.getX() << "   " << currentLocation.getY() << "    " << currentLocation.getHeading() << " " << endl;
}

float RobotMovement::CalculateAngleForMovemant(Pose * currentPosition, Pose * targetPosition)
{
	float radians = atan2((double)(targetPosition->y_() - currentPosition->getY()), (double)(targetPosition->x_() - currentPosition->getX()));
	float angle  = radians * (180.0/3.14);
	angle = NormalizeAngle(angle);

	float turnAngle = angle - currentPosition->getHeading();
	turnAngle = NormalizeAngle(turnAngle);
	cout << "the angle is : "   << angle << " to the next point, the currnt heading is :" << currentPosition->getHeading()
			<< " need to turn : " << turnAngle << "to left/right" << endl;

	return turnAngle;
}

bool RobotMovement::CheckIfArrive(Pose * currentPosition, Pose * targetPosition){
	bool isArrived = false;

	if((currentPosition->getX() > targetPosition->x_() - RANGE_BUFFER)&&
		(currentPosition->getX() < targetPosition->x_() + RANGE_BUFFER)&&
		(currentPosition->getY() > targetPosition->y_() - RANGE_BUFFER)&&
		(currentPosition->getY() < targetPosition->y_() + RANGE_BUFFER))
		{
			isArrived = true;
			cout << "ROBOT IN WAYPOINT!!! :)" << endl;
		}
	return isArrived;
}

float RobotMovement::NormalizeAngle(float angle){
	int newAngle = angle;
	if(newAngle < -180){
		newAngle += 360;
	}
	else if (angle > 180)
	{
		newAngle -= 360;
	}
	return newAngle;
}
