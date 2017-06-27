/*
 * HamsterAPIClientSimpleBehaviourExample.cpp
 *
 *  Created on: Aug 10, 2016
 *      Author: ofir
 */

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include "Robot.h"
using namespace std;
using namespace HamsterAPI;
using namespace cv;

int main(int argc, char ** argv)
{
	//Hamster* a = new HamsterAPI::Hamster(1);
	Robot* robot = new Robot();
	robot->start();
	delete robot;
	return 0;
}

/*
 int main() {
 try {
 HamsterAPI::Hamster * hamster = new HamsterAPI::Hamster(1);

 cv::namedWindow("OccupancyGrid-view");
 while (hamster->isConnected()) {
 try {

 OccupancyGrid ogrid = hamster->getSLAMMap();
 int width = ogrid.getWidth();
 int height = ogrid.getHeight();
 unsigned char pixel;
 //CvMat* M = cvCreateMat(width, height, CV_8UC1);
 cv::Mat m = cv::Mat(width, height,CV_8UC3);

 for (int i = 0; i < height; i++)
 for (int j = 0; j < width; j++) {
 if (ogrid.getCell(i, j) == CELL_FREE)
 pixel = 255;
 else if (ogrid.getCell(i, j) == CELL_OCCUPIED)
 pixel = 0;
 else
 pixel = 128;
 //cvmSet(M, i, j, pixel);
 m.at<Vec3b>(i,j)[0] = pixel;
 m.at<Vec3b>(i,j)[1] = pixel;
 m.at<Vec3b>(i,j)[2] = pixel;

 }

 cv::imshow("OccupancyGrid-view",m);
 cv::waitKey(1);

 } catch (const HamsterAPI::HamsterError & message_error) {
 HamsterAPI::Log::i("Client", message_error.what());
 }

 }
 } catch (const HamsterAPI::HamsterError & connection_error) {
 HamsterAPI::Log::i("Client", connection_error.what());
 }
 return 0;

 }
 */
