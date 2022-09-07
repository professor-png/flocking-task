#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2 AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 averageVelocity = Vector2::zero();
    unsigned int i = 0;

    // todo: add your code here to align each boid in a neighborhood
    // hint: iterate over the neighborhood
    for (i = 0; i < neighborhood.size(); i++)
    {
        averageVelocity += neighborhood[i]->getVelocity();
    }

    if (i != 0)
    {
        averageVelocity /= i;
    }

    return Vector2::normalized(averageVelocity);
}