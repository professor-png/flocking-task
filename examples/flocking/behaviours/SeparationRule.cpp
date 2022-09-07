#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

Vector2 SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Try to avoid boids too close
    Vector2 separatingForce = Vector2::zero();
    Vector2 dif;
    float inverse;

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
                dif = boid->getPosition() - neighborhood[i]->getPosition();
                inverse = 1 / dif.getMagnitude();
                dif = dif.normalized();
                dif *= inverse;
                separatingForce += dif;
            }
        }

        if (countCloseFlockmates != 0)
        {
            separatingForce /= countCloseFlockmates;
            //separatingForce *= separatingForce.getMagnitude();
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
