#ifndef CATCHER_H
#define CATCHER_H

#include "Agent.h"

struct WallPt
{
    Point2D point;
    int priority;

    WallPt(Point2D pt, int value);
};

class Catcher : public Agent
{
private:
    int originalDirection;
    Point2D startingPos;
    std::vector<WallPt> wallPositions;

    Point2D topLeft;
    Point2D topRight;
    Point2D bottomLeft;
    Point2D bottomRight;

public:
    explicit Catcher() :Agent() {};
    Point2D Move(World*) override;

    int getCatDirection(World* world);
    void setCornerPoints(int worldSize);
    Point2D getWallPt(World* world);
    void generateWallLocations(int worldSize);

    float distance(Point2D rhs, Point2D lhs);
};

#endif  // CATCHER_H
