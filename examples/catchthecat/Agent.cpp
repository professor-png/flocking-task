#include "Agent.h"

bool hex::operator<(const hex& rhs) const { return this->weight < rhs.weight; }
