#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  //visited.clear();
  //from.clear();

  //std::vector<hex> queue;
  //queue.push_back({world->getCat(), 0});

  //while (!queue.empty()) {
    //std::sort(queue.begin(), queue.end());
    //remove head
    //auto head = queue[0];
    //queue.erase(queue.begin());

    //mark head as visited
    //visited[head.point.x][head.point.y] = true;

    //if not visited add to queue with weight increased by 1
    //if (visited[queue[0].point.x][queue[0].point.y] == false)
    //  queue.push_back({head.point, head.weight+1});
    //mark where this element comes from
  //}
    setCornerPoints(world->getWorldSideSize());
    //clear queue
    visited.clear();
    from.clear();
    queue = std::priority_queue<hex>();

    //set first position in queue to cat current position
    visited[world->getCat().x][world->getCat().y] = true;
    queue.push({ world->getCat(), 0 });

    hex tmp = { world->getCat() , 0};
    hex origin;
    //hex head = queue.top();

    Point2D target = topLeft;

    //check to see if end goal has been reached
    while (origin.point != target)
    {
        origin = queue.top();
        queue.pop();

        // set tmp to NE point
        if (!world->getContent(World::NE(origin.point)))
        {
            tmp = { World::NE(origin.point), distance(World::NE(origin.point), target) };
            queue.push(tmp);
        }

        // set tmp to NW point
        if (!world->getContent(World::NW(origin.point)))
        {
            tmp = { World::NW(origin.point), distance(World::NW(origin.point), target) };
            queue.push(tmp);
        }

        // set tmp to E point
        if (!world->getContent(World::E(origin.point)))
        {
            tmp = { World::E(origin.point), distance(World::E(origin.point), target) };
            queue.push(tmp);
        }

        // set tmp to W point
        if (!world->getContent(World::W(origin.point)))
        {
            tmp = { World::W(origin.point), distance(World::W(origin.point), target) };
            queue.push(tmp);
        }

        // set tmp to SE point
        if (!world->getContent(World::SE(origin.point)))
        {
            tmp = { World::SE(origin.point), distance(World::SE(origin.point), target) };
            queue.push(tmp);
        }

        // set tmp to SW point
        if (!world->getContent(World::SW(origin.point)))
        {
            tmp = { World::SW(origin.point), distance(World::SW(origin.point), target) };
            queue.push(tmp);
        }
        from[queue.top().point.x][queue.top().point.y] = origin.point;
        visited[queue.top().point.x][queue.top().point.y] = true;

        return queue.top().point;
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
}

float Cat::distance(Point2D rhs, Point2D lhs)
{
    float distance;

    distance = pow(rhs.x - lhs.x, 2) + pow(rhs.y - lhs.y, 2);

    return sqrt(distance);
}