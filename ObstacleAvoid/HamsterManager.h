#include <HamsterAPIClientCPP/Hamster.h>

class HamsterManager
{
    public:
    
    HamsterManager() : m_hamster(1);

    void getScansBetween(double min, double max, std::vector<double> & distances);

    bool willCollide(std::vector<double> distances, int angle_from_center);

    int getCollisionsAmount(std::vector<double> distances, int angle_from_center);

    bool isFrontFree();

    // Gil & Maorchik
    int getRightCollisions();
    // Gil & Maorchik
    int getLeftCollisions();

    bool isLeftFree();

    bool isRightFree();

    bool isBackFree();

    void moveForward();

    void turnLeft();

    void turnRight();

    void moveBackwards();

    void stopMoving();

    HamsterAPI::Hamster m_hamster;
}