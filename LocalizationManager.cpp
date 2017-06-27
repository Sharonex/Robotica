/*
 * LocalizationManager.cpp
 *
 *  Created on: Jan 12, 2017
 *      Author: user
 */

#include "LocalizationManager.h"

using namespace manager;

void LocalizationManager::getRandomLocation(Particle* par)
{
	float x, y;
	do
	{
		x = rand() % ogrid.getWidth();
		y = rand() % ogrid.getHeight();
	} while (ogrid.getCell(x, y) != CELL_FREE);

	par->x = x * this->ogrid.getResolution();
	par->y = y * this->ogrid.getResolution();
	par->teta = rand() % 360;
}

LocalizationManager::LocalizationManager(const OccupancyGrid& ogrid) :
		ogrid(ogrid)
{
	particles.resize(NUM_OF_PARTICLES);
	initParticles();
}

void LocalizationManager::initParticles()
{
	for (int i = 0; i < NUM_OF_PARTICLES; i++)
	{
		particles[i] = new Particle();
		getRandomLocation(particles[i]);
	}
}

void LocalizationManager::updateParticles(HamsterAPI::LidarScan scan)
{
	this->scan = scan;
	vector<Particle *> addParticles;

	for (int i = 0; i < this->particles.size(); i++)
	{
		float belief = this->particles[i]->update(scan, this->ogrid);
		if (belief > HIGH_BELEIF)
		{
			createNewParticles(this->particles[i], &addParticles);
			cout << "add par = " << addParticles.size() << endl;
		}
		else if (belief < LOW_BELEIF)
		{
			this->particles.erase(this->particles.begin() + i);
			i--;
		}
	}
	cout << "done updating" << endl;
	int count = 0;
	int size = addParticles.size();
	vector<Particle*> p = this->particles;
	for (int i = 0; i < size; i++)
	{
		count = 0;
		for (int j = 0; j < particles.size(); j++)
		{
			if (!(this->particles[j] != addParticles[i]))
				count++;
		}
		if (count == 0)
			p.push_back(addParticles[i]);
	}

	this->particles = p;

	for (int i = 0; i < p.size(); i++)
		p[i]->print();

}

LocalizationManager::~LocalizationManager()
{

}

void LocalizationManager::createNewParticles(Particle* par,
		vector<Particle *>* newParticles)
{
	for (int i = -1; i < 2; i += 2)
	{
		for (int j = -1; j < 2; j += 2)
		{
			if (i == 0 && j == 0)
				continue;
			else
			{
				if (this->ogrid.getCell((par->x + i), (par->y + j))
						== CELL_FREE)
					newParticles->push_back(par->createParticle(i, j));
			}
		}
	}
	newParticles->push_back(par->createParticle(1, 1));
}
