#include "WindRule.h"
#include <imgui.h>
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

#include <iostream>
using namespace std;

Vector2 WindRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 windForce = Vector2::getVector2FromRadian(windAngle);

    return windForce;
}

bool WindRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    bool valueHasChanged = false;

    if (ImGui::SliderAngle("Wind Direction", &windAngle, 0)) {
        valueHasChanged = true;
    }

    return valueHasChanged;
}