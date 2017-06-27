#include "m_hamsterManager.h"

using namespace HamsterAPI;

class HamsterManager
{
    void getScansBetween(double min, double max, std::vector<double> & distances) {
        HamsterAPI::LidarScan scan = m_hamster->getLidarScan();

        for (size_t i = 0; i < scan.getScanSize(); i++) {
            double degree = scan.getScanAngleIncrement() * i;
            if (degree >= min && degree <= max)
                distances.push_back(scan.getDistance(i));
        }
    }

    bool willCollide(std::vector<double> distances, int angle_from_center) {
        HamsterAPI::LidarScan scan = m_hamster->getLidarScan();

        int collisions = 0;

        for (size_t i = distances.size() / 2 - angle_from_center / 2;
                i < distances.size() / 2 + angle_from_center / 2; i++)
            if (distances[i] < scan.getMaxRange() / 4.0)
                collisions++;

        return collisions >= angle_from_center / 4.0;
    }

    int getCollisionsAmount(std::vector<double> distances, int angle_from_center) {
        HamsterAPI::LidarScan scan = m_hamster->getLidarScan();

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
        m_hamster->sendSpeed(0.4, 0.0);
    }

    void turnLeft() {
        HamsterAPI::Log::i("Client", "Turning Left");
        while (!isFrontFree())
            m_hamster->sendSpeed(0.04, 45.0);
    }

    void turnRight() {
        HamsterAPI::Log::i("Client", "Turning Right");
        while (!isFrontFree())
            m_hamster->sendSpeed(0.04, -45.0);
    }

    void moveBackwards() {
        HamsterAPI::Log::i("Client", "Moving Backwards");
        while (!isLeftFree() && !isRightFree() && isBackFree())
            m_hamster->sendSpeed(-0.4, 0.0);
        if (isLeftFree())
            turnLeft();
        else
            turnRight();
    }

    void stopMoving() {
        m_hamster->sendSpeed(0.0, 0.0);
    }
}