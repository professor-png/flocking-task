#include "Catcher.h"
#include "World.h"

WallPt::WallPt(Point2D pt, int value)
{
    point = pt;
    priority = value;
}

Point2D Catcher::Move(World* world)
{
    if (wallPositions.size() == 0)
    {
        setCornerPoints(world->getWorldSideSize());
        generateWallLocations(world->getWorldSideSize());
    }

    Point2D tmp = getWallPt(world);//wallPositions[0].point;
    //wallPositions.erase(wallPositions.begin());
    return tmp;
}

int Catcher::getCatDirection(World* world)
{
    int i = 0;

    if (world->getCat() == World::NE(Point2D(0, 0)))
    {
        i = 1;
    }
    else if (world->getCat() == World::NW(Point2D(0, 0)))
    {
        i = 2;
    }
    else if (world->getCat() == World::W(Point2D(0, 0)))
    {
        i = 3;
    }
    else if (world->getCat() == World::E(Point2D(0, 0)))
    {
        i = 4;
    }
    else if (world->getCat() == World::SW(Point2D(0, 0)))
    {
        i = 5;
    }
    else if (world->getCat() == World::SE(Point2D(0, 0)))
    {
        i = 6;
    }

    return i;
}

void Catcher::setCornerPoints(int worldSize)
{
    int halfSize = worldSize / 2;

    // NE
    topRight.x = halfSize;
    topRight.y = -halfSize;

    // SE
    bottomRight.x = halfSize;
    bottomRight.y = halfSize;

    // NW
    topLeft.x = -halfSize;
    topLeft.y = -halfSize;

    // SW
    bottomLeft.x = -halfSize;
    bottomLeft.y = halfSize;
}

Point2D Catcher::getWallPt(World* world)
{
    Point2D tmp1, tmp2;
    float dist1 = 0, dist2 = 0, shortestDist1 = 100, shortestDist2 = 100;

    for (int i = 0; i < wallPositions.size(); i++)
    {
        if (wallPositions[i].priority == 1)
        {
            if (!world->getContent(wallPositions[i].point))
            {
                dist1 = distance(world->getCat(), wallPositions[i].point);

                if (dist1 < shortestDist1)
                {
                    shortestDist1 = dist1;
                    tmp1 = wallPositions[i].point;
                }
            }
        }
        else
        {
            if (!world->getContent(wallPositions[i].point))
            {
                dist2 = distance(world->getCat(), wallPositions[i].point);

                if (dist2 < shortestDist2)
                {
                    shortestDist2 = dist2;
                    tmp2 = wallPositions[i].point;
                }
            }
        }
    }

    //if all 1 priority spaces are full
    if (tmp1 == Point2D(0, 0))
        tmp1 = tmp2;

    if (shortestDist2 < shortestDist1 && shortestDist2 < 3)
        return tmp2;
    else
        return tmp1;
}

void Catcher::generateWallLocations(int worldSize)
{
    Point2D tmp = topLeft;
    int priority = 2;

    //generate top wall positions
    for (int i = 0; i < worldSize; i++)
    {
        wallPositions.push_back(WallPt(tmp, priority));
        tmp = World::E(tmp);

        if (priority == 1)
            priority = 2;
        else
            priority = 1;
    }

    tmp = topRight;
    for (int i = 0; i < worldSize; i++)
    {
        wallPositions.push_back(WallPt(tmp, priority));
        tmp = Point2D(tmp.x, tmp.y + 1);

        if (priority == 1)
            priority = 2;
        else
            priority = 1;
    }

    tmp = bottomRight;
    for (int i = 0; i < worldSize; i++)
    {
        wallPositions.push_back(WallPt(tmp, priority));
        tmp = World::W(tmp);

        if (priority == 1)
            priority = 2;
        else
            priority = 1;
    }

    tmp = bottomLeft;
    for (int i = 0; i < worldSize; i++)
    {
        wallPositions.push_back(WallPt(tmp, priority));
        tmp = Point2D(tmp.x, tmp.y - 1);

        if (priority == 1)
            priority = 2;
        else
            priority = 1;
    }
}

float Catcher::distance(Point2D rhs, Point2D lhs)
{
    float distance;

    distance = pow(rhs.x - lhs.x, 2) + pow(rhs.y - lhs.y, 2);

    return sqrt(distance);
}