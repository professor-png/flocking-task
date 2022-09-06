#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2 CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 cohesionForce;
    unsigned int i = 0;

    // todo: add your code here to make a force towards the center of mass
    // hint: iterate over the neighborhood
    for (i = 0; i < neighborhood.size(); i++)
    {
        cohesionForce += neighborhood[i]->getVelocity();
    }

    if (i != 0)
    {
        cohesionForce /= i;
    }

    //cohesionForce = Vector2::normalized(cohesionForce);

    return cohesionForce;
}