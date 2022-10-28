#include "MazeGenerator.h"
#include "World.h"

MazeGenerator::MazeGenerator()
{
	InitRandom(728954068);
}

bool MazeGenerator::Step(World* world)
{
	int direction;
	Point2D nextPt;
	//world->SetEast(Point2D(0, 0), false);
	//std::cout << Random(4) << std::endl;
	visited[startingPt.x][startingPt.y] = true;

	direction = Random(4);

	switch (direction)
	{
	case 1: // north
		break;
	case 2: // east
		break;
	case 3: // south
		break;
	case 4: // west
		break;
	}

	while 

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

void MazeGenerator::WorldChange(World* world)
{
	startingPt = Point2D(Random(world->GetSize()), Random(world->GetSize()));
	
	from.clear();

	for (int i = world->GetSize(); i > -world->GetSize(); i--)
	{
		for (int j = world->GetSize(); j > -world->GetSize(); j--)
		{
			visited[i][j] = false;
		}
	}
}
