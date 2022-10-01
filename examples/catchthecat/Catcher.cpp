#include "Catcher.h"
#include "World.h"

WallPt::WallPt(Point2D pt, int value)
{
    point = pt;
    priority = value;
}

Point2D Catcher::Move(World* world)
{
    /*if (world->getCat() == Point2D(0, 0))
    {*/
        //originalDirection = getCatDirection(world);
        //setCornerPoints(world->getWorldSideSize());

        //switch (originalDirection)
        //{
        //case 1: // cat moving NE
        //    std::cout << "NE\n";
        //    startingPos = Point2D(topRight.x, topRight.y + (world->getWorldSideSize() / 4));
        //    break;
        //case 2: // cat moving NE
        //    std::cout << "NW\n";
        //    startingPos = Point2D(topLeft.x, topLeft.y + (world->getWorldSideSize() / 4));
        //    break;
        //case 3: // cat moving W
        //    std::cout << "W\n";
        //    //startingPos = Point2D()
        //    break;
        //case 4: // cat moving E
        //    std::cout << "E\n";
        //    break;
        //case 5: // cat moving SW
        //    std::cout << "SW\n";
        //    break;
        //case 6: // cat moving SE
        //    std::cout << "SE\n";
        //    break;
        //}
    //}
    if (wallPositions.size() == 0)
    {
        setCornerPoints(world->getWorldSideSize());
        generateWallLocations(world->getWorldSideSize());
    }

    Point2D tmp = getWallPt(world);//wallPositions[0].point;
    //wallPositions.erase(wallPositions.begin());
    return tmp;
    /*auto side = world->getWorldSideSize() / 2;
    for (;;) {
        Point2D p = { Random::Range(-side, side), Random::Range(-side, side) };
        auto cat = world->getCat();
        if (cat.x != p.x && cat.y != p.y && !world->getContent(p))
            return p;
    }*/
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

    //NE
    topRight.x = halfSize;
    topRight.y = -halfSize;

    //SE
    bottomRight.x = halfSize;
    bottomRight.y = halfSize;

    //NW
    topLeft.x = -halfSize;
    topLeft.y = -halfSize;

    //SW
    bottomLeft.x = -halfSize;
    bottomLeft.y = halfSize;
}

Point2D Catcher::getWallPt(World* world)
{
    Point2D tmp;
    float dist = 0, shortestDist = distance(world->getCat(), wallPositions[0].point);

    for (int i = 1; i < wallPositions.size(); i++)
    {
        dist = distance(world->getCat(), wallPositions[i].point);

        if (dist < shortestDist && !world->getContent(wallPositions[i].point))
        {
            shortestDist = dist;
            tmp = wallPositions[i].point;
        }

    }

    return tmp;
}

void Catcher::generateWallLocations(int worldSize)
{
    Point2D tmp = topLeft;
    int priority = 1;

    //generate top wall positions
    for (int i = 0; i < worldSize - 1; i++)
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

    tmp = bottomLeft;
    for (int i = 0; i < worldSize - 1; i++)
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