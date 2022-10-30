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
		nextPt = Point2D(startingPt.x, startingPt.y + 1);
		break;
	case 2: // east
		nextPt = Point2D(startingPt.x + 1, startingPt.y);
		break;
	case 3: // south
		nextPt = Point2D(startingPt.x, startingPt.y - 1);
		break;
	case 4: // west
		nextPt = Point2D(startingPt.x - 1, startingPt.y);
		break;
	}

	world->SetNorth(nextPt, false);
	world->SetEast(nextPt, false);
	world->SetSouth(nextPt, false);
	world->SetWest(nextPt, false);
	startingPt = nextPt;
	//while ()

	return true;
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
	startingPt = Point2D(Random(world->GetSize() / 2), Random(world->GetSize() / 2));
	std::cout << startingPt.x << " " << startingPt.y << std::endl;
	
	from.clear();

	for (int i = world->GetSize(); i > -world->GetSize(); i--)
	{
		for (int j = world->GetSize(); j > -world->GetSize(); j--)
		{
			visited[i][j] = false;
		}
	}
}
