/*
 * RandomWalk.cpp
 *
 *  Created on: Jan 12, 2017
 *      Author: user
 */

#include "RandomWalk.h"
using namespace robotics;

RandomWalk::RandomWalk(HamsterAPI::Hamster * hamster)
{
	// TODO Auto-generated constructor stub
	this->hamster = hamster;
	moveBack = false;
	moveLeft = false;
	moveRight = false;
}

RandomWalk::RandomWalk()
{

}

RandomWalk::~RandomWalk()
{
	// TODO Auto-generated destructor stub
}

void RandomWalk::walk(HamsterAPI::LidarScan scan)
{
	this->scan = scan;
	if (isFrontFree() && (!moveBack) && (!moveLeft) && (!moveRight))
	{
		moveForward();
		//moveBack = false;
		//moveLeft = false;
		//moveRight = false;
	}
	else
	{
		turning();
	}
}

bool RandomWalk::isFrontFree()
{
	// Degrees : [90, 270]

	std::vector<double> distances;

	getScansBetween(90, 270, distances);

	return !willCollide(distances, 40);
}

bool RandomWalk::isLeftFree()
{
	// Degrees : [180,360]

	std::vector<double> distances;

	getScansBetween(180, 360, distances);

	return !willCollide(distances, 40);
}

bool RandomWalk::isRightFree()
{
	// Degrees : [0, 180]

	std::vector<double> distances;

	getScansBetween(0, 180, distances);

	return !willCollide(distances, 40);
}

bool RandomWalk::isBackFree()
{
	// Degrees : [270,360], [0, 90]

	std::vector<double> distances;

	getScansBetween(315, 360, distances);
	getScansBetween(0, 45, distances);

	return !willCollide(distances, 40);
}

void RandomWalk::moveForward()
{
	//HamsterAPI::Log::i("Client", "Moving Forward");
	this->hamster->sendSpeed(0.4, 0.0);
}

void RandomWalk::turnLeft()
{
	HamsterAPI::Log::i("Client", "Turning Left");
	this->moveLeft = true;
	if (isFrontFree())
		this->moveLeft = false;
	else if (isLeftFree())
		this->hamster->sendSpeed(0.4, 45.0);
	else
	{
		this->moveLeft = false;
		return;
	}
}

void RandomWalk::turnRight()
{
	HamsterAPI::Log::i("Client", "Turning Right");
	this->moveRight = true;
	if (isFrontFree())
		this->moveRight = false;
	else if (isRightFree())
		this->hamster->sendSpeed(0.4, -45.0);
	else
	{
		this->moveRight = false;
		return;
	}
}

void RandomWalk::moveBackwards()
{
	//HamsterAPI::Log::i("Client", "Moving Backwards");
	this->moveBack = true;
	if (isLeftFree())
	{
		this->moveBack = false;
		moveLeftBack();
	}
	else if (isRightFree())
	{
		this->moveBack = false;
		moveRightBack();
	}
	else if (isBackFree())
		this->hamster->sendSpeed(-0.4, 0.0);
	else
	{
		this->moveBack = false;
		return;
	}
}

void RandomWalk::moveRightBack()
{
	for (int i = 0; i < 150000; i++)
	{
		this->hamster->sendSpeed(-0.4, -45.0);
	}
}

void RandomWalk::moveLeftBack()
{
	for (int i = 0; i < 150000; i++)
	{
		this->hamster->sendSpeed(-0.4, 45.0);
	}
}

void RandomWalk::stopMoving()
{
	int i = 0;
	while (i < 300000)
	{
		/*if(i<50000)
		 this->hamster->sendSpeed(-0.3, 0.0);
		 else if(i<100000)
		 this->hamster->sendSpeed(-0.2, 0.0);
		 else if(i<150000)
		 this->hamster->sendSpeed(-
		 0.1, 0.0);
		 else*/
		this->hamster->sendSpeed(0.0, 0.0);
		i++;
		printf("%d\n", i);
	}
}

void RandomWalk::getScansBetween(double min, double max,
		std::vector<double> & distances)
{

	for (size_t i = 0; i < this->scan.getScanSize(); i++)
	{
		double degree = this->scan.getScanAngleIncrement() * i;
		if (degree >= min && degree <= max)
			distances.push_back(this->scan.getDistance(i));
	}
}

double RandomWalk::CalcMHWScore(vector<double> scores)
{
	double median;
	size_t size = scores.size();

	sort(scores.begin(), scores.end());

	if (size % 2 == 0)
	{
		median = (scores[size / 2 - 1] + scores[size / 2]) / 2;
	}
	else
	{
		median = scores[size / 2];
	}

	return median;
}

bool RandomWalk::willCollide(std::vector<double> distances,
		int angle_from_center)
{

	int collisions = 0;

	for (size_t i = distances.size() / 2 - angle_from_center / 2;
			i < distances.size() / 2 + angle_from_center / 2; i++)
		if (distances[i] < this->scan.getMaxRange() / 6.0)
			collisions++;

	return collisions >= angle_from_center / 6.0;
}

void RandomWalk::turning()
{
	cout << "turning" << endl;
	bool leftFree = isLeftFree();
	bool rightFree = isRightFree();
	int randNum;

	if (this->moveBack)
	{
		moveBackwards();
	}
	else if (this->moveLeft)
	{
		turnLeft();
	}
	else if (this->moveRight)
	{
		turnRight();
	}
	else if (leftFree && rightFree)
	{		//random turn
		randNum = rand() % 2;
		if (randNum == 0)
			turnRight();
		else
			turnLeft();
	}
	else if (!(leftFree || rightFree))
	{		//backwards
		moveBackwards();
	}
	else if (leftFree)
	{		//left
		turnLeft();
	}
	else
	{		//right
		turnRight();
	}

	/*if(leftFree && rightFree){//random turn
	 randNum = rand()%2;
	 if(randNum == 0)
	 turnRight();
	 else
	 turnLeft();
	 }
	 else if(!(leftFree || rightFree)){//backwards
	 moveBackwards();
	 }
	 else if(leftFree){//left
	 turnLeft();
	 }
	 else{//right
	 turnRight();
	 }*/
}

/*double TML=0,TMR=0;
 //bool back = false;
 //int j = 0;
 cout<<"turning"<<endl;
 std::vector<double> distances,DT1,DT2;
 getScansBetween(90, 270, distances);
 if(willCollide(distances, 40) == false)
 {
 for(unsigned int i=0;i<distances.size();i++)
 {
 if(i<=90)
 DT1.push_back(distances[i]);
 if(i>=90)
 DT2.push_back(distances[i]);
 }
 TML = CalcMHWScore(DT1);//Left
 TMR = CalcMHWScore(DT2);//Right
 cout<<"TML = "<<TML<<",TMR = "<<TMR<<endl;

 if(!(TML <1.00 && TMR<1.00))
 {
 cout<<"hello"<<endl;
 if(TML < TMR){
 turnLeft();
 moveBack = false;
 }
 else if(TMR >= TML){
 moveBack = false;
 turnRight();
 }

 }
 else{
 moveBack = true;
 moveBackwards();
 }
 else
 {
 back = true;
 for(j=0;j<100000;j++)
 {
 if(j<20000)
 this->hamster->sendSpeed(0.3, 0.0);
 else if(j<45000)
 this->hamster->sendSpeed(0.2, 0.0);
 else if(j<70000)
 this->hamster->sendSpeed(0.1, 0.0);
 else
 this->hamster->sendSpeed(0.0, 0.0);
 }
 while(back == true)
 {
 moveBackwards();
 if(isLeftFree())
 {
 back = false;
 for(j=0;j<300000;j++)
 {
 if(j<50000)
 this->hamster->sendSpeed(-0.3, -45);
 else if(j<11000)
 this->hamster->sendSpeed(-0.2, -45);
 else if(j<150000)
 this->hamster->sendSpeed(-0.1, -45);
 else if(j<200000)
 this->hamster->sendSpeed(0.0, 0.0);
 else if(j<220000)
 this->hamster->sendSpeed(0.1, 45);
 else if(j<220000)
 this->hamster->sendSpeed(0.2, 45);
 else if(j<250000)
 this->hamster->sendSpeed(0.3, 45);
 else if(j<270000)
 this->hamster->sendSpeed(0.4, 45);
 }

 }
 else if(isRightFree())
 {
 back = false;
 for(j=0;j<300000;j++)
 {
 if(j<50000)
 this->hamster->sendSpeed(-0.3, 45);
 else if(j<11000)
 this->hamster->sendSpeed(-0.2, 45);
 else if(j<150000)
 this->hamster->sendSpeed(-0.1, 45);
 else if(j<200000)
 this->hamster->sendSpeed(0.0, 0.0);
 else if(j<220000)
 this->hamster->sendSpeed(0.1, -45);
 else if(j<220000)
 this->hamster->sendSpeed(0.2, -45);
 else if(j<250000)
 this->hamster->sendSpeed(0.3, -45);
 else if(j<270000)
 this->hamster->sendSpeed(0.4, -45);
 }
 }
 }
 }
 }
 else{
 moveBack = true;
 moveBackwards();
 if(!(TML <1.00 && TMR<1.00))moveBack = false;
 }
 }*/
