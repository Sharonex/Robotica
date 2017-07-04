/*
 * HamsterAPIClientSimpleBehaviourExample.cpp
 *
 *  Created on: Aug 10, 2016
 *      Author: ofir
 */
#include <HamsterAPIClientCPP/Hamster.h>

#include "HamsterManager.h"
#include <iostream>

using namespace std;
using namespace HamsterAPI;

HamsterAPI::Hamster* hamster;

/***
 * Random walk. Turn to the better way.
 */
int evenDerechA1() 
{
	try 
	{
		HamsterManager hamster_man;

		cv::namedWindow("OccupancyGrid-view");
		while (hamster_man.isConnected())
		{
			try 
			{
				if (hamster_man.isFrontFree())
				{
					hamster_man.moveForward();
				}
				else 
				{
					hamster_man.stopMoving();
					if (hamster_man.isLeftFree() || hamster_man.isRightFree())
					{
						if (hamster_man.getRightCollisions() < hamster_man.getLeftCollisions())
							hamster_man.turnRight();
						else
							hamster_man.turnLeft();
					} 
					else if (hamster_man.isBackFree())
					{
						hamster_man.moveBackwards();
					}
					else
					{
						HamsterAPI::Log::i("Client", "I am stuck!");
					}
				}
			} 
			catch (const HamsterAPI::HamsterError & message_error) 
			{
				HamsterAPI::Log::i("Client", message_error.what());
			}
		}
	} 
	catch (const HamsterAPI::HamsterError & connection_error) 
	{
		HamsterAPI::Log::i("Client", connection_error.what());
	}

	return 0;
}

bool safe_paint(cv::Mat& m, int x, int y)
{
	return x >= 0 && x < m.cols && y >= 0 && y < m.rows;
}

void paintInNewMap(int x, int y, cv::Mat& m, int radius, unsigned char color)
{
	for(int i = x-radius; i < x + radius; i++)
	{
		for (int j = y-radius; j < y + radius; j++)
		{
			if (safe_paint(m,i,j))
			{
				m.at<unsigned char>(i,j) = color;
			}
		}
	}
}

int evenDerechB(OccupancyGrid& ogrid, int robotsize)
{
	try
	{
		cv::namedWindow("OccupancyGrid-view");

		int newRes = 1 * robotsize;
		int rad = newRes / 2;

		OccupancyGrid newOg = hamster->getSLAMMap();

		int newWidth = ogrid.getWidth() * rad;
		int newHeight = ogrid.getHeight() * rad;
		cv::Mat m = cv::Mat(newWidth, newHeight, CV_8UC1);

		for (int i = 0; i < newWidth; i++)
		{
			for (int j = 0; j < newHeight; j++)
			{
				m.at<unsigned char>(i, j) = CELL_FREE;
			}
		}

		/*for (int i = 0; i < ogrid.getWidth(); i++)
		{
			for (int j = 0; j < ogrid.getHeight(); j++)
			{
				if (ogrid.getCell(i, j) != CELL_FREE)
				{
					paintInNewMap(i,j,m,rad,static_cast<unsigned char>(ogrid.getCell(i, j)));
				}
			}
		}*/

		sleep(4);
		printf("AAAAAAAAHHHHHHH\r\n");
		cv::imshow("OccupancyGrid-view", m);
		cv::waitKey(1000);
	} 
	catch (const HamsterAPI::HamsterError & connection_error)
	{
		HamsterAPI::Log::i("Client", connection_error.what());
	}

	return 0;
}

int main()
{
	hamster = new HamsterAPI::Hamster(1);

	try
	{
		cv::namedWindow("OccupancyGrid-view");

		sleep(3);

		while (hamster->isConnected())
		{
			OccupancyGrid og = hamster->getSLAMMap();
			evenDerechB(og, 2);
			sleep(100000);
			return 0;
		}
	} catch (const HamsterAPI::HamsterError & connection_error)
	{
		hamster->disconnect();
		HamsterAPI::Log::i("Client", connection_error.what());
	}

	return 0;
}

