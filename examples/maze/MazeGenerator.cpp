#include "MazeGenerator.h"
#include "World.h"

MazeGenerator::MazeGenerator()
{
	InitRandom(728954068);
}

bool MazeGenerator::Step(World* world)
{
	int direction = 1;
	Point2D nextPt = startingPt;
	//world->SetEast(Point2D(0, 0), false);
	//std::cout << Random(4) << std::endl;
	visited[startingPt.x][startingPt.y] = true;
	world->SetNodeColor(startingPt, Color::Red.Dark());

	std::cout << visited.size() << std::endl;

	while (nextPt == startingPt)
	{
		direction = Random(4);

		if (direction == 1) // north
		{
			nextPt = Point2D(startingPt.x, startingPt.y - 1);
			//world->SetSouth(startingPt, false);
		}
		
		if (direction == 2) // east
		{
			nextPt = Point2D(startingPt.x + 1, startingPt.y);
			//world->SetWest(startingPt, false);
		}	
		
		if (direction == 3) // south
		{
			nextPt = Point2D(startingPt.x, startingPt.y + 1);
			//world->SetNorth(startingPt, false);
		}	
		
		if (direction == 4) // west
		{
			nextPt = Point2D(startingPt.x - 1, startingPt.y);
			//world->SetEast(startingPt, false);
		}

		if (nextPt == last)
			nextPt = startingPt;

		if (!world->isValidPosition(nextPt) || visited[nextPt.x][nextPt.y] == true)
		{
			Hunt(world);
			nextPt = startingPt;
			break;
		}
	}

	
	if (nextPt == Point2D(startingPt.x, startingPt.y - 1)) // north
		world->SetSouth(nextPt, false);

	if (nextPt == Point2D(startingPt.x + 1, startingPt.y)) // east
		world->SetWest(nextPt, false);

	if (nextPt == Point2D(startingPt.x, startingPt.y + 1)) // south
		world->SetNorth(nextPt, false);

	if (nextPt == Point2D(startingPt.x - 1, startingPt.y)) // west
		world->SetEast(nextPt, false);

	//visited[startingPt.x][startingPt.y] = true;
	last = startingPt;
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

	//from.clear();

	for (int i = world->GetSize() / 2; i >= -world->GetSize() / 2; i--)
	{
		for (int j = world->GetSize() / 2; j >= -world->GetSize() / 2; j--)
		{
			visited[i][j] = false;
		}
	}
}

void MazeGenerator::Hunt(World* world)
{
	std::cout << "World size: " << world->GetSize() << std::endl;
	for (int i = -world->GetSize() / 2; i <= world->GetSize() / 2; i++)
	{
		for (int j = -world->GetSize() / 2; j <= world->GetSize() / 2; j++)
		{
			if (visited[j][i] == false)
			{
				startingPt = Point2D(j, i);
				//visited[startingPt.x][startingPt.y] = true;
				return;
			}
		}
	}
}
