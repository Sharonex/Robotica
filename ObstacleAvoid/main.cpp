/*
 * HamsterAPIClientSimpleBehaviourExample.cpp
 *
 *  Created on: Aug 10, 2016
 *      Author: ofir
 */

#include "HamsterManager.h"
#include <iostream>

using namespace std;

enum SECTOR_COLOR {
	WHITE = 255, BLACK = 0, GRAY = 128
};

SECTOR_COLOR GetSectorColor(OccupancyGrid& ogrid, int start_x, int start_y,
		int sector_size) {
	int pixel_sum = 0;

	int height =
			ogrid.getHeight() >= (start_y + sector_size) ?
					sector_size : ogrid.getHeight();
	int width =
			ogrid.getWidth() >= (start_x + sector_size) ?
					sector_size : ogrid.getWidth();
	for (int i = start_x; i < start_x + height; i += 1) {
		for (int j = start_y;  j < start_y + width; j += 1) {
			int cell_val = ogrid.getCell(i, j);
			if (cell_val != CELL_FREE)
			{
				pixel_sum++;
			}
		}
	}
	//printf("Sum is: %d\r\n", pixel_sum);
	if (pixel_sum == 0)
		return WHITE;
	else if (pixel_sum == sector_size*sector_size)
		return BLACK;

	return GRAY;
}

/***
 * Random walk. Turn to the better way.
 */
int evenDerechA1() {
	try {
		//hamster = new HamsterAPI::Hamster(1);

		cv::namedWindow("OccupancyGrid-view");
		while (hamster->isConnected()) {

			try {
				if (isFrontFree()) {
					moveForward();
				} else {
					stopMoving();
					if (isLeftFree() || isRightFree()) {
						if (getRightCollisions() < getLeftCollisions())
							turnRight();
						else
							turnLeft();
					} else if (isBackFree())
						moveBackwards();
					else
						HamsterAPI::Log::i("Client", "I am stuck!");
				}
				/*	}
				 else if (isLeftFree())
				 turnLeft();
				 else if (isRightFree())
				 turnRight();
				 else if (isBackFree())
				 moveBackwards();
				 else
				 HamsterAPI::Log::i("Client", "I am stuck!");
				 }
				 */
			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}

		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}

	return 0;
}

int evenDerechB(OccupancyGrid& ogrid, int robotsize) {
	try {
		cv::namedWindow("OccupancyGrid-view");
		int width = ogrid.getWidth();
		int height = ogrid.getHeight();
		unsigned char pixel = 0;

		cv::Mat m = cv::Mat(width / robotsize, height  / robotsize, CV_8UC1);
		printf("matrix dimensions: (%d, %d)\n", height, width);

		// get cell status and init cell color
		for (int i = 0; i < height; i += 1)
			for (int j = 0; j < width; j += 1) {

				 pixel = 0;
				 if (ogrid.getCell(i, j) == CELL_OCCUPIED)
					 pixel = 255;

				 //cvmSet(M, i, j, pixel);
				 m.at<unsigned char>(i, j) = pixel;

				pixel = GetSectorColor(ogrid, i, j, robotsize);
			}

				// Show map
			cv::imshow("OccupancyGrid-view", m);
			cv::waitKey(1000);
		}
	catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
	return 0;

}

int main() {
	try {
		cv::namedWindow("OccupancyGrid-view");
		hamster = new HamsterAPI::Hamster(1);
		sleep(3);

		while (hamster->isConnected()) {
			OccupancyGrid og = hamster->getSLAMMap();
			evenDerechB(og, 4);
			sleep(3);
		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
	//evenDerechA1();

	return 0;
}

