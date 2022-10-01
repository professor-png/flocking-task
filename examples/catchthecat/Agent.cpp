#include "Agent.h"

bool hex::operator<(const hex& rhs) const { return rhs.weight < this->weight; }
