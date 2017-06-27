/*
 * HamsterAPIClientSimpleBehaviourExample.cpp
 *
 *  Created on: Aug 10, 2016
 *      Author: ofir
 */

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
using namespace std;
using namespace HamsterAPI;
HamsterAPI::Hamster * hamster;

void getScansBetween(double min, double max, std::vector<double> & distances) {
	HamsterAPI::LidarScan scan = hamster->getLidarScan();

	for (size_t i = 0; i < scan.getScanSize(); i++) {
		double degree = scan.getScanAngleIncrement() * i;
		if (degree >= min && degree <= max)
			distances.push_back(scan.getDistance(i));
	}
}

bool willCollide(std::vector<double> distances, int angle_from_center) {
	HamsterAPI::LidarScan scan = hamster->getLidarScan();

	int collisions = 0;

	for (size_t i = distances.size() / 2 - angle_from_center / 2;
			i < distances.size() / 2 + angle_from_center / 2; i++)
		if (distances[i] < scan.getMaxRange() / 4.0)
			collisions++;

	return collisions >= angle_from_center / 4.0;
}

int getCollisionsAmount(std::vector<double> distances, int angle_from_center) {
	HamsterAPI::LidarScan scan = hamster->getLidarScan();

	int collisions = 0;

	for (size_t i = distances.size() / 2 - angle_from_center / 2;
			i < distances.size() / 2 + angle_from_center / 2; i++)
		if (distances[i] < scan.getMaxRange() / 4.0)
			collisions++;
	return collisions;
}
bool isFrontFree() {
	// Degrees : [90, 270]

	std::vector<double> distances;

	getScansBetween(90, 270, distances);

	return !willCollide(distances, 40);
}

// Gil & Maorchik
int getRightCollisions() {
	std::vector<double> distances;

	getScansBetween(0, 180, distances);
	return getCollisionsAmount(distances, 40);
}

// Gil & Maorchik
int getLeftCollisions() {
	std::vector<double> distances;

	getScansBetween(180, 360, distances);
	return getCollisionsAmount(distances, 40);
}

bool isLeftFree() {
	// Degrees : [180,360]

	std::vector<double> distances;

	getScansBetween(180, 360, distances);

	return !willCollide(distances, 40);
}

bool isRightFree() {
	// Degrees : [0, 180]

	std::vector<double> distances;

	getScansBetween(0, 180, distances);

	return !willCollide(distances, 40);
}

bool isBackFree() {
	// Degrees : [270,360], [0, 90]

	std::vector<double> distances;

	getScansBetween(270, 360, distances);
	getScansBetween(0, 90, distances);

	return !willCollide(distances, 40);
}

void moveForward() {
	HamsterAPI::Log::i("Client", "Moving Forward");
	hamster->sendSpeed(0.4, 0.0);
}

void turnLeft() {
	HamsterAPI::Log::i("Client", "Turning Left");
	while (!isFrontFree())
		hamster->sendSpeed(0.04, 45.0);
}

void turnRight() {
	HamsterAPI::Log::i("Client", "Turning Right");
	while (!isFrontFree())
		hamster->sendSpeed(0.04, -45.0);
}

void moveBackwards() {
	HamsterAPI::Log::i("Client", "Moving Backwards");
	while (!isLeftFree() && !isRightFree() && isBackFree())
		hamster->sendSpeed(-0.4, 0.0);
	if (isLeftFree())
		turnLeft();
	else
		turnRight();
}

void stopMoving() {
	hamster->sendSpeed(0.0, 0.0);
}

int Oldmain(int argc, char ** argv) {
	try {
		hamster = new HamsterAPI::Hamster(1);
		while (hamster->isConnected()) {
			try {
				if (isFrontFree())
					moveForward();
				else {
					stopMoving();
					if (isLeftFree())
						turnLeft();
					else if (isRightFree())
						turnRight();
					else if (isBackFree())
						moveBackwards();
					else
						HamsterAPI::Log::i("Client", "I am stuck!");
				}

				// Speed Getter
				// HamsterAPI::Speed speed = hamster.getSpeed();
			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}

		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
	return 0;
}

int Oldmain2(int argc, char ** argv) {
	try {
		hamster = new HamsterAPI::Hamster(1);
		/*OccupancyGrid ogrid = hamster->getSLAMMap();
		 cout<< "resolution: "<< ogrid.getResolution()<<endl;
		 cout<< "Width: "<< ogrid.getWidth()<<endl;
		 cout<< "height: "<< ogrid.getHeight()<<endl;
		 */
		while (hamster->isConnected()) {
			try {
				HamsterAPI::LidarScan ld = hamster->getLidarScan();
				if (ld.getDistance(180) < 0.4) {

					hamster->sendSpeed(-0.5, 0);
					cout << "Front: " << ld.getDistance(180) << endl;
				} else if (ld.getDistance(180) < 0.8) {
					hamster->sendSpeed(0.5, 45);
					cout << "Front: " << ld.getDistance(180) << endl;
				}

				else
					hamster->sendSpeed(1.0, 0);
				//cout<<"Front: "<<ld.getDistance(180)<<endl;
				//cout<<"Left: "<<ld.getDistance(90)<<endl;
				//cout<<"Right: "<<ld.getDistance(270)<<endl;
			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}

		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
	return 0;
}

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
			//printf("In cell (%d, %d) value is: %d\n", i,j,ogrid.getCell(i,j));
			int cell_val = ogrid.getCell(i, j);
			if (cell_val != CELL_FREE)
			{
				pixel_sum++;
			}
			//pixel_sum += (ogrid.getCell(i, j) == CELL_OCCUPIED) ? 1 : 0;
		}
	}
	//printf("Sum is: %d\r\n", pixel_sum);
	if (pixel_sum == 0)
		return WHITE;
	else if (pixel_sum == sector_size*sector_size)
		return BLACK;

	return GRAY;
}

int evenDerechB(OccupancyGrid& ogrid, int robotsize) {
	try {
		//hamster = new HamsterAPI::Hamster(1);

		cv::namedWindow("OccupancyGrid-view");
		/*OccupancyGridCreator creator;
		creator.setOccupancyGrid(const_cast<const OccupancyGrid&>(ogrid));
		creator.resolution = ogrid.getResolution();
		creator.h = ogrid.getHeight();
		creator.w = ogrid.getWidth();
		creator.resize();

		OccupancyGrid new_grid = creator.create();
*/
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

int main() {
	cout << "F";
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

