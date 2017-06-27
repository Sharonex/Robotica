/*
 * Map.cpp
 *
 *  Created on: Jan 16, 2017
 *      Author: user
 */

#include "Map.h"
#include <iostream>

using namespace std;

Map::Map(const OccupancyGrid& ogrid):ogrid(ogrid){
	// TODO Auto-generated constructor stub
	//cout<<ogrid.toString()<<endl;
	//drawMap();
}

void Map::drawMap(const vector<Particle*> *particles) {
	try {
			int width = ogrid.getWidth();
			int height = ogrid.getHeight();
			unsigned char pixel;
			//CvMat* M = cvCreateMat(width, height, CV_8UC1);
			cv::Mat m = cv::Mat(width, height,CV_8UC3);

			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j++) {
					if (ogrid.getCell(i, j) == CELL_FREE)
					{
						pixel = 255;
					}
					else if (ogrid.getCell(i, j) == CELL_OCCUPIED)
						pixel = 0;
					else
						pixel = 128;
					//cvmSet(M, i, j, pixel);

					/*for(int z = 0;z<particles.size();z++)
					{
						int x = particles[z]->x;
						int y = particles[z]->y;
						if(x==i && y==z)

					}*/
					m.at<Vec3b>(i,j)[0] = pixel;
					m.at<Vec3b>(i,j)[1] = pixel;
					m.at<Vec3b>(i,j)[2] = pixel;
				}
			for(int z = 0;z<particles->size();z++)
			{
				int x = (*particles)[z]->x /this->ogrid.getResolution();
				int y = (*particles)[z]->y/this->ogrid.getResolution();
				m.at<Vec3b>(x,y)[0] = 0;
				m.at<Vec3b>(x,y)[1] = 0;
				m.at<Vec3b>(x,y)[2] = 255;
			}

			//cv::namedWindow("OccupancyGrid-view",CV_WINDOW_NORMAL);
			cv::imshow("OccupancyGrid-view",m);
			cv::waitKey(1);
			//cout<<"start drawing"<<endl;
		} catch (const HamsterAPI::HamsterError & message_error) {
			HamsterAPI::Log::i("Client", message_error.what());
		}
		//cout<<"start drawing2"<<endl;
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

