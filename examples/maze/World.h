#ifndef MOBAGEN_WORLD_H
#define MOBAGEN_WORLD_H

#include "ColorT.h"
#include "GameObject.h"
#include "MazeGenerator.h"
#include "Node.h"
#include "Point2D.h"
#include <vector>

#include "generators/RecursiveBacktracker.h"

class World : GameObject {
private:
    int sideSize;

    MazeGenerator generator;
    //RecursiveBacktracker generator;
    bool isSimulating = false;
    float timeBetweenAITicks = 1;
    float timeForNextTick = 1;
    int64_t moveDuration = 0;

    // .=
    // |
    // even indexes are top elements;
    // odd indexes are left elements;
    std::vector<bool> data;
    // the boxes colors
    std::vector<Color32> colors;
    // convert a point into the index of the left vertex of the node
    inline int Point2DtoIndex(const Point2D& point) {
        // todo: test. unstable interface
        auto sizeOver2 = sideSize / 2;
        return (point.y + sizeOver2) * (sideSize + 1) * 2 + (point.x + sizeOver2) * 2;
    }
public:
    explicit World(Engine* pEngine, int size);

    Node GetNode(const Point2D& point);
    bool GetNorth(const Point2D& point);
    bool GetEast(const Point2D& point);
    bool GetSouth(const Point2D& point);
    bool GetWest(const Point2D& point);

    bool isValidPosition(const Point2D& p);

    void SetNode(const Point2D& point, const Node& node);
    void SetNorth(const Point2D& point, const bool& state);
    void SetEast(const Point2D& point, const bool& state);
    void SetSouth(const Point2D& point, const bool& state);
    void SetWest(const Point2D& point, const bool& state);

    void Start() override;
    void OnGui(ImGuiContext* context) override;
    void OnDraw(SDL_Renderer* renderer) override;
    void Update(float deltaTime) override;

    void Clear();

    void SetNodeColor(const Point2D& node, const Color32& color);

    int GetSize() const;
private:
    void step();
};

#endif
