#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

Vector2 SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Try to avoid boids too close
    Vector2 separatingForce = Vector2::zero();
    

    float desiredDistance = desiredMinimalDistance;

    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
    if (!neighborhood.empty())
    {
        int countCloseFlockmates = 0;

        for (unsigned int i = 0; i < neighborhood.size(); i++)
        {
            if (boid->getPosition().getDistance(boid->getPosition(), neighborhood[i]->getPosition()) < desiredDistance)
            {
                countCloseFlockmates++;
                separatingForce += boid->getPosition() - neighborhood[i]->getPosition();
            }
        }

        if (countCloseFlockmates != 0)
        {
            separatingForce /= countCloseFlockmates;
        }
    }

    separatingForce = Vector2::normalized(separatingForce);

    return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    bool valusHasChanged = false;

    if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
        valusHasChanged = true;
    }

    return valusHasChanged;
}
