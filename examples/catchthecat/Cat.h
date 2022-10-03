#ifndef CAT_H
#define CAT_H

#include "Agent.h"
#include <queue>

class Cat: public Agent
{
 private:
  std::priority_queue<hex> queue;
  std::unordered_map<int, std::unordered_map<int, bool>> pointsInQueue;

  //(0,0 is in center of grid)
  Point2D topLeft;
  Point2D topRight;
  Point2D bottomLeft;
  Point2D bottomRight;

  Point2D target;

 public:
    explicit Cat():Agent(){};
    Point2D Move(World *) override;
    void setVisited(int worldSize);
    void setCornerPoints(int worldSize);
    float distance(Point2D rhs, Point2D lhs);
};

#endif  // CAT_H
