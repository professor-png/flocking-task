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

    Point2D tmp = getWallPt(world);

    return tmp;
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

    //if all wall spaces are full
    if (tmp1 == Point2D(0, 0) && tmp2 == Point2D(0, 0))
    {
        //tmp1 = world->getCat();
        while (world->getContent(tmp1))
        {
            int rand = Random::Range(0, 5);
            Point2D pos = world->getCat();
            switch (rand)
            {
            case 0:
                tmp1 = World::NE(pos);
                break;
            case 1:
                tmp1 = World::NW(pos);
                break;
            case 2:
                tmp1 = World::E(pos);
                break;
            case 3:
                tmp1 = World::W(pos);
                break;
            case 4:
                tmp1 = World::SW(pos);
                break;
            default:
                tmp1 = World::SE(pos);
                break;
            }
        }
    }

    if (shortestDist2 < shortestDist1 && shortestDist2 < 3)
        return tmp2;
    else
        return tmp1;
}

void Catcher::generateWallLocations(int worldSize)
{
    Point2D tmp = World::E(topLeft);
    int priority = 2;

    //generate top wall positions
    for (int i = 0; i < worldSize - 2; i++)
    {
        wallPositions.push_back(WallPt(tmp, priority));
        tmp = World::E(tmp);

        if (priority == 1)
            priority = 2;
        else
            priority = 1;
    }

    tmp = topRight;
    for (int i = 0; i < worldSize - 1; i++)
    {
        wallPositions.push_back(WallPt(tmp, priority));
        tmp = Point2D(tmp.x, tmp.y + 1);

        if (priority == 1)
            priority = 2;
        else
            priority = 1;
    }

    tmp = bottomRight;
    for (int i = 0; i < worldSize - 1; i++)
    {
        wallPositions.push_back(WallPt(tmp, priority));
        tmp = World::W(tmp);

        if (priority == 1)
            priority = 2;
        else
            priority = 1;
    }

    tmp = World::NE(bottomLeft);
    for (int i = 0; i < worldSize - 2; i++)
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