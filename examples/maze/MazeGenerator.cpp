#include "MazeGenerator.h"
#include "World.h"

MazeGenerator::MazeGenerator()
{
	InitRandom(728954068);
}

bool MazeGenerator::Step(World* world)
{
	//world->SetEast(Point2D(0, 0), false);
	std::cout << Random(4) << std::endl;

	return false;
}
void MazeGenerator::Clear(World* world) {}

void MazeGenerator::InitRandom(int seed)
{
	random.seed(seed);
}

int MazeGenerator::Random(int bounds)
{
	return random() % bounds + 1;
}