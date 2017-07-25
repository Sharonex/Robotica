/*
 * Map.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: user
 */

#include "Map.h"
#define BELIEF_LIMIT 0.9
Map::Map(OccupancyGrid &ogrid) : ogrid(ogrid), mat(ogrid.getWidth(), ogrid.getHeight(), CV_8UC3, cv::Scalar(255, 255, 255)) {
	cv::namedWindow("Map");
}

void Map::initMap() {
	for (int i = 0; i < ogrid.getHeight(); i++) {
		for (int j = 0; j < ogrid.getWidth(); j++) {

			Cell c = ogrid.getCell(i, j);
			if (c == CELL_FREE) {
				mat.at<cv::Vec3b>(i, j)[0] = 255;
				mat.at<cv::Vec3b>(i, j)[1] = 255;
				mat.at<cv::Vec3b>(i, j)[2] = 255;
			}
			else if (c == CELL_OCCUPIED)
			{
				mat.at<cv::Vec3b>(i, j)[0] = 0;
				mat.at<cv::Vec3b>(i, j)[1] = 0;
				mat.at<cv::Vec3b>(i, j)[2] = 0;
			}
			else
			{
				mat.at<cv::Vec3b>(i, j)[0] = 150;
				mat.at<cv::Vec3b>(i, j)[1] = 150;
				mat.at<cv::Vec3b>(i, j)[2] = 150;

			}
		}
	}
}

void Map::drawParticles(vector<Particle *> particles) {
	initMap();

	for (int i = 0; i < particles.size(); i++) {
		Particle *p = particles[i];
		if (particles[i]->belief<BELIEF_LIMIT){
			mat.at<cv::Vec3b>(p->j, p->i)[0] = 0;
			mat.at<cv::Vec3b>(p->j, p->i)[1] = 0;
			mat.at<cv::Vec3b>(p->j, p->i)[2] = 255;
		}
		else{
			mat.at<cv::Vec3b>(p->j, p->i)[0] = 255;
			mat.at<cv::Vec3b>(p->j, p->i)[1] = 0;
			mat.at<cv::Vec3b>(p->j, p->i)[2] = 0;
		}
		if(i>=particles.size()-5) {
			mat.at<cv::Vec3b>(p->j, p->i)[0] = 0;
			mat.at<cv::Vec3b>(p->j, p->i)[1] = 255;
			mat.at<cv::Vec3b>(p->j, p->i)[2] = 0;
		}
	}
}

void Map::showMap() {
	// Show the matrix on the window
	cv::imshow("Map", mat);

	// Delay for 1 millisecond to allow the window to process
	// incoming events
	cv::waitKey(1);
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

