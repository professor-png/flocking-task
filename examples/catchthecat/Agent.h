#ifndef AGENT_H
#define AGENT_H
#include "Point2D.h"
#include <unordered_map>

class World;

struct hex {
  Point2D point;
  float weight = 0;
  int distTraveled = 0;
  bool operator<(const hex& rhs) const;
};

class Agent {
public:
  explicit Agent()= default;;
  virtual Point2D Move(World*)=0;

  std::unordered_map<int, std::unordered_map<int, bool>> visited;
  std::unordered_map<int, std::unordered_map<int, hex>> from;
};

#endif  // AGENT_H
