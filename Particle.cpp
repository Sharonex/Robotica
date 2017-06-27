/*
 * Particle.cpp
 *
 *  Created on: Jan 12, 2017
 *      Author: user
 */

#include "Particle.h"

Particle::Particle(float x, float y, float teta) {
   this->x = x;
   this->y = y;
   this->teta = teta;
   this->belief = 0.6;
}

float Particle::update(HamsterAPI::LidarScan scan,const OccupancyGrid& ogrid) {
	//update belief particle
    printf("updating\n");
	int hits = 0;
	int misses = 0;
	//cout<<scan.toString()<<endl;
	for (size_t i = 0; i<scan.getScanSize();i++)
	{
		//in radian
		double angle = scan.getScanAngleIncrement() * i * DEG2RAD;
		//bodek shen micshol
		//if the call and we call 3.999
		if(scan.getDistance(i) < scan.getMaxRange() - 0.001)
		{
			//obstracle_pos = particle_pos+scan_disntannce*cos (heading + scan angel)
			double obsX = this->x*ogrid.getResolution() + scan.getDistance(i) * cos(angle + this->teta * DEG2RAD + 180 * DEG2RAD);
			double obsY = this->y*ogrid.getResolution() + scan.getDistance(i) * sin(angle + this->teta * DEG2RAD + 180 * DEG2RAD);

			int pixelsX = (obsX / (ogrid.getResolution()));
			int pixelsY = (obsY / (ogrid.getResolution()));
			//check if have hits
			//cout<<x/ogrid.getResolution()<<" "<<y/ogrid.getResolution()<<endl;
			//cout<<obsX<<" "<<obsY<<endl;
			//cout<<pixelsX<<" "<<pixelsY<<" "<<ogrid.getCell(pixelsX , pixelsY)<<endl;
			if(ogrid.getCell(pixelsX , pixelsY) == CELL_OCCUPIED)
			{
				hits++;
			}
			else {
				misses++;
			}
		}
	}


	printf("%d %d\n",hits,misses);
	this->belief = (float)hits / (hits + misses);
	printf("b = %f\n",this->belief);
	return this->belief;
}

//create particle
Particle* Particle::createParticle(int right_left_X,int up_down_Y) {
		return new Particle(this->x+right_left_X,this->y+up_down_Y,this->teta);
}

float Particle::getBelief() {
	return this->belief;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

Particle::Particle() {
	   this->belief = 0.6;
}

bool Particle::operator!=(const Particle p) const {
	return (this->x!=p.x)||(this->y!=p.y);
}

void Particle::print() {
	cout<<"("<<this->x<<","<<this->y<<","<<this->teta<<") "<<this->belief<<endl;
}


