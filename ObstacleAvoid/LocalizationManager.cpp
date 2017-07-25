/*
 * LocalizationManager.cpp
 *
 *  Created on: Jan 11, 2017
 *      Author: user
 */

#include "LocalizationManager.h"
#include <iostream>
#include <math.h>

using namespace std;
#define PARTICLES_NUM 300
#define MAGNIFYING_NUM 100000

LocalizationManager::LocalizationManager(const OccupancyGrid &ogrid,
		Hamster *hamster) :
		ogrid(ogrid), hamster(hamster) {
	// TODO Auto-generated constructor stub
	cout << "width: " << ogrid.getWidth() << ", height: " << ogrid.getHeight()
			<< endl;
}

void LocalizationManager::getRandomLocation(Particle *particle) {
	do {
		particle->j = rand() % ogrid.getWidth();
		particle->i = rand() % ogrid.getHeight();

	} while (ogrid.getCell(particle->j, particle->i) != CELL_FREE);

	particle->x = (particle->j - (double) ogrid.getWidth() / 2)
			* ogrid.getResolution();
	particle->y = ((double) ogrid.getHeight() / 2 - particle->i)
			* ogrid.getResolution();

//	cout << "x: " << particle->x << ", y: " << particle->y << ", i: " << particle->i << ", j: " << particle->j << endl;
	particle->yaw = rand() % 360;
}

void LocalizationManager::initParticles() {
	particles.resize(PARTICLES_NUM);

	for (int i = 0; i < particles.size(); i++) {
		particles[i] = new Particle();
		getRandomLocation(particles[i]);

	}
}

double LocalizationManager::computeBelief(Particle *particle, LidarScan scan) {
	//LidarScan scan = hamster->getLidarScan();

	int hits = 0;
	int misses = 0;

	for (int i = 0; i < scan.getScanSize(); i++) {
		double angle = scan.getScanAngleIncrement() * i * DEG2RAD;

		if (scan.getDistance(i) < scan.getMaxRange() - 0.001) {
			// Obstacle_Pos = Particle_Pos + Scan_Distance * cos (Heading + Scan Angle)
			// SWITCH COS AND SIN
			double obsX = particle->x + scan.getDistance(i) * sin(angle + particle->yaw * DEG2RAD - 180 * DEG2RAD);
			double obsY = particle->y + scan.getDistance(i) * cos(angle + particle->yaw * DEG2RAD - 180 * DEG2RAD);

			int pixelsi = ((double) ogrid.getWidth() / 2) + (obsX / ogrid.getResolution());
			int pixelsj = ((double) ogrid.getHeight() / 2) - (obsY / ogrid.getResolution());

			if (ogrid.getCell(pixelsi, pixelsj) == CELL_OCCUPIED) {
				hits++;
			} else {
				misses++;
			}
			//cout << "hits : "<< hits <<" misses : "<< misses <<"belief : "<< (float)hits / (hits + misses)<<endl;
		}
	}
	return (float) hits / (hits + misses);
}

void LocalizationManager::updateParticles(double deltaX, double deltaY, double deltaYaw, LidarScan scan) {
	for (int i = 0; i < particles.size(); i++) {
		Particle *particle = particles[i];
		particle->x += deltaX * cos(particle->yaw * DEG2RAD);
		particle->y += deltaY * sin(particle->yaw * DEG2RAD);
		particle->yaw += deltaYaw;
		particle->i = (double) ogrid.getHeight() / 2 - particle->y / ogrid.getResolution();
		particle->j = particle->x / ogrid.getResolution() + ogrid.getWidth() / 2;

		if (ogrid.getCell(particle->j, particle->i) == CELL_UNKNOWN)
			getRandomLocation(particle);
		particle->belief = computeBelief(particle, scan);
	}
}

void LocalizationManager::evolveParticles() {
	sortParticles();

	int particlesSize = particles.size();
	double sum;

	for (int i = 0; i < particlesSize; i++) {
		sum += particles[i]->belief;
	}

	double avg = sum / PARTICLES_NUM * 1.5;
	double remainingParticlesAvg = 0;
	double totalBelief = 0;
	int numDeletedParticles = particles.size() * 0.3;

	for (int i = numDeletedParticles; i < particlesSize; i++) {
		totalBelief += (particles[i]->belief);
		remainingParticlesAvg += (particles[i]->belief);
	}

	double numRandomParticles = MIN(numDeletedParticles * pow(1 - avg, 2), numDeletedParticles * 0.7);
	remainingParticlesAvg = remainingParticlesAvg / (particles.size() - numDeletedParticles);

	//just if have a bad average will pick random particles
	if (remainingParticlesAvg < 0.2) {
		for (int i = 0; i < numRandomParticles; i++) {
			if (particles[i]->belief < 0.5)
				getRandomLocation(particles[i]);
			else
				createBestParticleNeighbour(particles[i]);
		}
	}

	cout << "Better Particles AVG :" << remainingParticlesAvg << " Top Particle Belief :" << particles[PARTICLES_NUM - 1]->belief << endl;

	//just if have a good belief will pick near particles
	if (particles[PARTICLES_NUM - 1]->belief > 0.4) {
		for (int j = numRandomParticles; j < numDeletedParticles; j++) {
			int r = rand() % ((int)totalBelief * MAGNIFYING_NUM);
			int t = 0;
			for (int i = numDeletedParticles; i < particlesSize; ++i) {
				t += (particles[i]->belief) * MAGNIFYING_NUM;
				if (r < t) {
					createParticleNeighbour(particles[j], particles[i]);
				}
			}
		}
	}
}
void LocalizationManager::createBestParticleNeighbour(Particle *targetParticle) {
	createParticleNeighbour(targetParticle, particles[PARTICLES_NUM - 1]);
}

void LocalizationManager::createParticleNeighbour(Particle *targetParticle, Particle *sourceParticle) {
	do {
		targetParticle->j = (rand() % 5) + (sourceParticle->j - 2);
		targetParticle->i = (rand() % 5) + (sourceParticle->i - 2);

	} while (ogrid.getCell(targetParticle->j, targetParticle->i) != CELL_FREE);

	targetParticle->x = (targetParticle->j - (double) ogrid.getWidth() / 2) * ogrid.getResolution();
	targetParticle->y = ((double) ogrid.getHeight() / 2 - targetParticle->i) * ogrid.getResolution();

//cout << "x: " << targetParticle->x << ", y: " << targetParticle->y << ", i: " << targetParticle->i << ", j: " << targetParticle->j << endl;
	targetParticle->yaw = sourceParticle->yaw + (rand() % 16) - 8;
}

void LocalizationManager::printParticles() const {
	for (int i = 0; i < particles.size(); i++) {
		Particle *particle = particles[i];
//		cout << "Particle " << i << ": " << particle->x << "," << particle->y << ", belief: " << particle->belief << endl;
	}
}

vector<Particle *> LocalizationManager::getParticles() const {
	return particles;
}

void LocalizationManager::sortParticles() {
	int pos_min;
	for (int i = 0; i < particles.size(); i++) {
		pos_min = i;
		for (int j = i + 1; j < particles.size(); j++) {
			if (particles[j]->belief < particles[pos_min]->belief)
				pos_min = j;
		}
		if (pos_min != i) {
			Particle *temp = particles[i];
			particles[i] = particles[pos_min];
			particles[pos_min] = temp;
		}
	}
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}

