#ifndef CAT_H
#define CAT_H

#include "Agent.h"
#include <queue>

class Cat: public Agent
{
 private:
  std::priority_queue queue;

 public:
    explicit Cat():Agent(){};
    Point2D Move(World *) override;
};

#endif  // CAT_H
