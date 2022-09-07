#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2 CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 cohesionForce = Vector2::zero();
    unsigned int i = 0;

    // todo: add your code here to make a force towards the center of mass
    // hint: iterate over the neighborhood
    for (i = 0; i < neighborhood.size(); i++)
    {
        cohesionForce += neighborhood[i]->getPosition();
    }

    if (i != 0)
    {
        cohesionForce /= i;
    }
    
    cohesionForce -= boid->getPosition();
    
    cohesionForce = cohesionForce.normalized();

    return cohesionForce;
}