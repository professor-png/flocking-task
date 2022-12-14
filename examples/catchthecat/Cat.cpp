#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
    if (topRight == Point2D(0, 0))
        setCornerPoints(world->getWorldSideSize());
    //clear queue
    visited.clear();
    setVisited(world->getWorldSideSize());
    from.clear();
    queue = std::priority_queue<hex>();
    pointsInQueue.clear();
    
    //set first position in queue to cat current position
    visited[world->getCat().x][world->getCat().y] = true;
    pointsInQueue[world->getCat().x][world->getCat().y] = true;
    queue.push({ world->getCat(), 0 });

    hex tmp = { world->getCat() , 0};
    hex origin;

    //check to see if end goal has been reached
    while (abs(queue.top().point.x) != world->getWorldSideSize() / 2 || abs(queue.top().point.y) != world->getWorldSideSize() / 2) //(origin.point != target)
    {
        origin = queue.top();
        pointsInQueue[queue.top().point.x][queue.top().point.y] = false;
        queue.pop();

        visited[origin.point.x][origin.point.y] = true;

        // set tmp to NE point
        if (world->isValidPosition(World::NE(origin.point)) && !world->getContent(World::NE(origin.point)) && visited[World::NE(origin.point).x][World::NE(origin.point).y] == false && pointsInQueue[World::NE(origin.point).x][World::NE(origin.point).y] != true)
        {
            tmp = { World::NE(origin.point), distance(World::NE(origin.point), target), origin.distTraveled + 1 };
            queue.push(tmp);
            pointsInQueue[tmp.point.x][tmp.point.y] = true;
            from[World::NE(origin.point).x][World::NE(origin.point).y] = origin;
        }

        // set tmp to NW point
        if (world->isValidPosition(World::NW(origin.point)) && !world->getContent(World::NW(origin.point)) && visited[World::NW(origin.point).x][World::NW(origin.point).y] == false && pointsInQueue[World::NW(origin.point).x][World::NW(origin.point).y] != true)
        {
            tmp = { World::NW(origin.point), distance(World::NW(origin.point), target), origin.distTraveled + 1 };
            queue.push(tmp);
            pointsInQueue[tmp.point.x][tmp.point.y] = true;
            from[World::NW(origin.point).x][World::NW(origin.point).y] = origin;
        }

        // set tmp to E point
        if (world->isValidPosition(World::E(origin.point)) && !world->getContent(World::E(origin.point)) && visited[World::E(origin.point).x][World::E(origin.point).y] == false && pointsInQueue[World::E(origin.point).x][World::E(origin.point).y] != true)
        {
            tmp = { World::E(origin.point), distance(World::E(origin.point), target), origin.distTraveled + 1 };
            queue.push(tmp);
            pointsInQueue[tmp.point.x][tmp.point.y] = true;
            from[World::E(origin.point).x][World::E(origin.point).y] = origin;
        }

        // set tmp to W point
        if (world->isValidPosition(World::W(origin.point)) && !world->getContent(World::W(origin.point)) && visited[World::W(origin.point).x][World::W(origin.point).y] == false && pointsInQueue[World::W(origin.point).x][World::W(origin.point).y] != true)
        {
            tmp = { World::W(origin.point), distance(World::W(origin.point), target), origin.distTraveled + 1 };
            queue.push(tmp);
            pointsInQueue[tmp.point.x][tmp.point.y] = true;
            from[World::W(origin.point).x][World::W(origin.point).y] = origin;
        }

        // set tmp to SE point
        if (world->isValidPosition(World::SE(origin.point)) && !world->getContent(World::SE(origin.point)) && visited[World::SE(origin.point).x][World::SE(origin.point).y] == false && pointsInQueue[World::SE(origin.point).x][World::SE(origin.point).y] != true)
        {
            tmp = { World::SE(origin.point), distance(World::SE(origin.point), target), origin.distTraveled + 1 };
            queue.push(tmp);
            pointsInQueue[tmp.point.x][tmp.point.y] = true;
            from[World::SE(origin.point).x][World::SE(origin.point).y] = origin;
        }

        // set tmp to SW point
        if (world->isValidPosition(World::SW(origin.point)) && !world->getContent(World::SW(origin.point)) && visited[World::SW(origin.point).x][World::SW(origin.point).y] == false && pointsInQueue[World::SW(origin.point).x][World::SW(origin.point).y] != true)
        {
            tmp = { World::SW(origin.point), distance(World::SW(origin.point), target), origin.distTraveled + 1 };
            queue.push(tmp);
            pointsInQueue[tmp.point.x][tmp.point.y] = true;
            from[World::SW(origin.point).x][World::SW(origin.point).y] = origin;
        }

        //see if there is somewhere for the cat to go
        if (queue.empty() == true)
        {
            //if there is nowhere to go return current position
            if (world->getContent(World::NE(world->getCat())) && world->getContent(World::NW(world->getCat())) && world->getContent(World::E(world->getCat())) && world->getContent(World::W(world->getCat())) && world->getContent(World::SE(world->getCat())) && world->getContent(World::SW(world->getCat())))
                return world->getCat();
            else
            {
                target = origin.point;
                
                visited.clear();
                setVisited(world->getWorldSideSize());
                from.clear();
                queue = std::priority_queue<hex>();
                pointsInQueue.clear();

                //set first position in queue to cat current position
                visited[world->getCat().x][world->getCat().y] = true;
                pointsInQueue[world->getCat().x][world->getCat().y] = true;
                queue.push({ world->getCat(), 0 });

                tmp = { world->getCat() , 0 };
            }
        }

        if (abs(queue.top().point.x) == world->getWorldSideSize() / 2 || abs(queue.top().point.y) == world->getWorldSideSize() / 2 || queue.top().point == target)
        {
            if (!world->getContent(queue.top().point))
            {
                target = queue.top().point;
                break;
            }
        }
    }

    tmp.point = target;
    Point2D oneBefore = tmp.point;
    
    //track back to the cat
    while (tmp.point != world->getCat())
    {
        oneBefore = tmp.point;
        tmp = from[tmp.point.x][tmp.point.y];
    }
    
    return oneBefore;
}

void Cat::setVisited(int worldSize)
{
    worldSize /= 2;

    for (int i = worldSize; i > -worldSize; i--)
    {
        for (int j = worldSize; j > -worldSize; j--)
        {
            visited[i][j] = false;
        }
    }
}

void Cat::setCornerPoints(int worldSize)
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

    int rand = Random::Range(0, 4);

    switch (rand)
    {
    case 1:
        target = topLeft;
        break;
    case 2:
        target = topRight;
        break;
    case 3:
        target = bottomLeft;
        break;
    case 4:
        target = bottomRight;
        break;
    default:
        target = topLeft;
        break;
    }
}

float Cat::distance(Point2D rhs, Point2D lhs)
{
    float distance;

    distance = pow(rhs.x - lhs.x, 2) + pow(rhs.y - lhs.y, 2);

    return sqrt(distance);
}