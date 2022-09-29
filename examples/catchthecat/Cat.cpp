#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  visited.clear();
  from.clear();

  std::vector<hex> queue;
  queue.push_back({world->getCat(), 0});

  while (!queue.empty()) {
    std::sort(queue.begin(), queue.end());
    //remove head
    auto head = queue[0];
    queue.erase(queue.begin());
    //mark head as visited
    visited[head.point.x][head.point.y] = true;
    //if not visited add to queue with weight increased by 1
    if (visited[queue[0].point.x][queue[0].point.y] == false)
      queue.push_back({head.point, head.weight+1});
    //mark where this element comes from
  }


  auto rand = Random::Range(0,5);
  auto pos = world->getCat();
  switch(rand){
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);
    case 3:
      return World::W(pos);
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
}

void Cat::setCornerPoints(int worldSize)
{ 
    int halfSize = worldSize / 2;

    topRight.x = halfSize;
    topRight.y = halfSize;

    bottomRight.x = halfSize;
    bottomRight.y = -halfSize;

    topLeft.x = -halfSize;
    topLeft.y = halfSize;

    bottomLeft.x = -halfSize;
    bottomLeft.y = -halfSize;
}
