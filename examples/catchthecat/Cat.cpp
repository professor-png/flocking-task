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
    //visited.clear();
    setVisited(world->getWorldSideSize());
    from.clear();
    queue = std::priority_queue<hex>();

    //set first position in queue to cat current position
    visited[world->getCat().x][world->getCat().y] = true;
    queue.push({ world->getCat(), 0 });

    hex tmp = { world->getCat() , 0};
    hex origin;

    Point2D target = topLeft;

    //check to see if end goal has been reached
    while (abs(origin.point.x) != world->getWorldSideSize() / 2 || abs(origin.point.y) != world->getWorldSideSize() / 2) //(origin.point != target)
    {
        //std::cout << queue.top().point.x << " " << queue.top().point.y << " Visited:  " << visited[queue.top().point.x][queue.top().point.y] << std::endl;
        //std::cout << queue.top().point.x << " " << queue.top().point.y << std::endl;
        origin = queue.top();
        queue.pop();
        
        from[queue.top().point.x][queue.top().point.y] = origin.point;
        visited[origin.point.x][origin.point.y] = true;

        // set tmp to NE point
        if (world->isValidPosition(World::NE(origin.point)) && !world->getContent(World::NE(origin.point)) && visited[World::NE(origin.point).x][World::NE(origin.point).y] == false)
        {
            tmp = { World::NE(origin.point), distance(World::NE(origin.point), target) };
            queue.push(tmp);
            //std::cout << "trigger NE\n";
        }

        // set tmp to NW point
        if (world->isValidPosition(World::NW(origin.point)) && !world->getContent(World::NW(origin.point)) && visited[World::NW(origin.point).x][World::NW(origin.point).y] == false)
        {
            tmp = { World::NW(origin.point), distance(World::NW(origin.point), target) };
            queue.push(tmp);
            //std::cout << "trigger NW\n";
        }

        // set tmp to E point
        if (world->isValidPosition(World::E(origin.point)) && !world->getContent(World::E(origin.point)) && visited[World::E(origin.point).x][World::E(origin.point).y] == false)
        {
            tmp = { World::E(origin.point), distance(World::E(origin.point), target) };
            queue.push(tmp);
            //std::cout << "trigger E\n";
        }

        // set tmp to W point
        if (world->isValidPosition(World::W(origin.point)) && !world->getContent(World::W(origin.point)) && visited[World::W(origin.point).x][World::W(origin.point).y] == false)
        {
            tmp = { World::W(origin.point), distance(World::W(origin.point), target) };
            queue.push(tmp);
            //std::cout << "trigger W\n";
        }

        // set tmp to SE point
        if (world->isValidPosition(World::SE(origin.point)) && !world->getContent(World::SE(origin.point)) && visited[World::SE(origin.point).x][World::SE(origin.point).y] == false)
        {
            tmp = { World::SE(origin.point), distance(World::SE(origin.point), target) };
            queue.push(tmp);
            //std::cout << "trigger SE\n";
        }

        // set tmp to SW point
        if (world->isValidPosition(World::SW(origin.point)) && !world->getContent(World::SW(origin.point)) && visited[World::SW(origin.point).x][World::SW(origin.point).y] == false)
        {
            tmp = { World::SW(origin.point), distance(World::SW(origin.point), target) };
            queue.push(tmp);
            //std::cout << "trigger SW\n";
        }
    }

    tmp.point = target;
    //std::cout << tmp.point.x << " " << tmp.point.y << " From: " << from[tmp.point.x][tmp.point.y].x << from[tmp.point.x][tmp.point.y].y << std::endl;
    Point2D oneBefore = tmp.point;

    //for (int i = world->getWorldSideSize() / 2; i > -world->getWorldSideSize() / 2; i--)
    //{
    //    for (int j = world->getWorldSideSize() / 2; j > -world->getWorldSideSize() / 2; j--)
    //    {
    //        //std::cout << i << " " << j << std::endl;
    //        if (visited[i][j] == 1)
    //            std::cout << "true\n";
    //    }
    //}

    while (tmp.point != world->getCat())
    {
        oneBefore = tmp.point;
        tmp.point = from[tmp.point.x][tmp.point.y];
        std::cout << "Loop\n";
    }
    std::cout << oneBefore.x << " " << oneBefore.y << std::endl;
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
}

float Cat::distance(Point2D rhs, Point2D lhs)
{
    float distance;

    distance = pow(rhs.x - lhs.x, 2) + pow(rhs.y - lhs.y, 2);

    return sqrt(distance);
}