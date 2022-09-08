#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

Vector2 BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Return a force proportional to the proximity of the boids with the bounds, and opposed to it
    Vector2 force = Vector2::zero(); //zero
    Vector2 sizeWindow = this->world->engine->window->size();

    // todo: add here your code code here do make the boid follow the bounded box rule
    // hint: use this->world->engine->window->size() and desiredDistance
    if (boid->getPosition().x < desiredDistance)
        force.x += 1;
    else if (boid->getPosition().x > sizeWindow.x - desiredDistance)
        force.x += -1;

    if (boid->getPosition().y < desiredDistance)
        force.y += 1;
    else if (boid->getPosition().y > sizeWindow.y - desiredDistance)
        force.y += -1;

    return force;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    auto size = this->world->engine->window->size();
    auto widthWindows = size.x;
    auto heightWindows = size.y;
    bool valueHasChanged = false;

    //We cap the max separation as the third of the min of the width.height
    auto minHeightWidth = std::min(widthWindows, heightWindows);

    if (ImGui::SliderInt("Desired Distance From Borders",
                         &desiredDistance,
                         0.0f,
                         (int)(minHeightWidth/3),
                         "%i")) {
        valueHasChanged = true;
    }

    return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
    FlockingRule::draw(boid, renderer);
    auto size = this->world->engine->window->size();
    auto dist = (float)desiredDistance;

    // Draw a rectangle on the map
    Polygon::DrawLine(renderer, Vector2(dist,dist), Vector2(size.x - dist,dist), Vector3::Gray()); // TOP
    Polygon::DrawLine(renderer, Vector2(size.x - dist,dist), Vector2(size.x - dist,size.y - dist), Vector3::Gray()); // RIGHT
    Polygon::DrawLine(renderer, Vector2(size.x - dist,size.y - dist), Vector2(dist,size.y - dist), Vector3::Gray()); // Bottom
    Polygon::DrawLine(renderer, Vector2(dist,size.y - dist), Vector2(dist,dist), Vector3::Gray()); // LEFT
}