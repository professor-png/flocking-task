#include "MazeGenerator.h"
#include "World.h"

MazeGenerator::MazeGenerator()
{
	InitRandom(728954068);
}

bool MazeGenerator::Step(World* world)
{
	int direction, oppositeDir;
	Point2D nextPt = startingPt;
	//world->SetEast(Point2D(0, 0), false);
	//std::cout << Random(4) << std::endl;
	visited[startingPt.x][startingPt.y] = true;

	direction = Random(4);

	while ()
	switch (direction)
	{
	case 1: // north
		nextPt = Point2D(startingPt.x, startingPt.y + 1);
		oppositeDir = 0;
		world->SetSouth(nextPt, false);
		break;
	case 2: // east
		nextPt = Point2D(startingPt.x + 1, startingPt.y);
		oppositeDir = 1;
		world->SetWest(nextPt, false);
		break;
	case 3: // south
		nextPt = Point2D(startingPt.x, startingPt.y - 1);
		oppositeDir = 2;
		world->SetNorth(nextPt, false);
		break;
	case 4: // west
		nextPt = Point2D(startingPt.x - 1, startingPt.y);
		oppositeDir = 3;
		world->SetEast(nextPt, false);
		break;
	}

	if (visited[nextPt.x][nextPt.y] == true)
	{
		std::cout << "visited\n";
	}

	/*world->SetNorth(nextPt, false);
	world->SetEast(nextPt, false);
	world->SetSouth(nextPt, false);
	world->SetWest(nextPt, false);*/
	visited[startingPt.x][startingPt.y] = true;
	startingPt = nextPt;

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
	
	int negative = Random(4);

	switch (negative)
	{
	case 1: // (pos, pos)
		break;
	case 2: // (pos, neg)
		startingPt.y *= -1;
		break;
	case 3: // (neg, pos)
		startingPt.x *= -1;
		break;
	case 4: // (neg, neg)
		startingPt.x *= -1;
		startingPt.y *= -1;
		break;
	}

	from.clear();

	for (int i = world->GetSize(); i > -world->GetSize(); i--)
	{
		for (int j = world->GetSize(); j > -world->GetSize(); j--)
		{
			visited[i][j] = false;
		}
	}
}
