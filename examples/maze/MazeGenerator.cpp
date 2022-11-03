#include "MazeGenerator.h"
#include "World.h"

MazeGenerator::MazeGenerator()
{
	InitRandom(SEED);
}

bool MazeGenerator::Step(World* world)
{
	bool foundPos = true;
	int direction = 1;
	nextPt = startingPt;
	//world->SetNodeColor(startingPt, Color::Red.Dark());

	for (int i = -world->GetSize() / 2; i <= world->GetSize() / 2; i++)
	{
		for (int j = -world->GetSize() / 2; j <= world->GetSize() / 2; j++)
		{
			world->SetNodeColor(Point2D(j, i), Color::Black.Dark());
		}
	}

	while (nextPt == startingPt)
	{
		direction = Random(4);

		if (direction == 1 && last != Point2D(startingPt.x, startingPt.y - 1)) // north
		{
			nextPt = Point2D(startingPt.x, startingPt.y - 1);
			//world->SetSouth(startingPt, false);
		}
		
		if (direction == 2 && last != Point2D(startingPt.x + 1, startingPt.y)) // east
		{
			nextPt = Point2D(startingPt.x + 1, startingPt.y);
			//world->SetWest(startingPt, false);
		}	
		
		if (direction == 3 && last != Point2D(startingPt.x, startingPt.y + 1)) // south
		{
			nextPt = Point2D(startingPt.x, startingPt.y + 1);
			//world->SetNorth(startingPt, false);
		}	
		
		if (direction == 4 && last != Point2D(startingPt.x - 1, startingPt.y)) // west
		{
			nextPt = Point2D(startingPt.x - 1, startingPt.y);
			//world->SetEast(startingPt, false);
		}

		if (!world->IsValidPosition(nextPt) || visited[nextPt.x][nextPt.y] == true)
		{
			foundPos = Hunt(world);
			//nextPt = startingPt;
			break;
		}
	}

	if (foundPos)
	{
		if (nextPt == Point2D(startingPt.x, startingPt.y - 1)) // north
			world->SetSouth(nextPt, false);

		if (nextPt == Point2D(startingPt.x + 1, startingPt.y)) // east
			world->SetWest(nextPt, false);

		if (nextPt == Point2D(startingPt.x, startingPt.y + 1)) // south
			world->SetNorth(nextPt, false);

		if (nextPt == Point2D(startingPt.x - 1, startingPt.y)) // west
			world->SetEast(nextPt, false);

		visited[startingPt.x][startingPt.y] = true;
		last = startingPt;
		startingPt = nextPt;

		return true;
	}

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

bool MazeGenerator::Hunt(World* world)
{
	Point2D foundPt;

	for (int i = -world->GetSize() / 2; i <= world->GetSize() / 2; i++)
	{
		for (int j = -world->GetSize() / 2; j <= world->GetSize() / 2; j++)
		{
			if (visited[j][i] == false)
			{
				//world->SetNodeColor(Point2D(j, i), Color::Red.Dark());
				foundPt = FindNeighbors(Point2D(j, i), world);

				if (foundPt != Point2D(INT_MAX, INT_MAX))
				{
					//std::cout << foundPt.x << " " << foundPt.y << std::endl;
					//std::cout << visited[-2][-10] << std::endl;
					visited[startingPt.x][startingPt.y] = true;
					world->SetNodeColor(foundPt, Color::Red.Dark());
					startingPt = foundPt;//Point2D(j, i);
					visited[foundPt.x][foundPt.y] = true;
					return true;
				}
			}
		}
	}

	return false;
}

Point2D MazeGenerator::FindNeighbors(Point2D pt, World* world)
{
	if (visited[pt.x][pt.y + 1] /*&& world->IsValidPosition(Point2D(pt.x, pt.y + 1))*/) // north
	{
		nextPt = Point2D(pt.x, pt.y + 1);
		return pt;
	}

	else if (visited[pt.x - 1][pt.y] /*&& world->IsValidPosition(Point2D(pt.x - 1, pt.y))*/) // east
	{
		nextPt = Point2D(pt.x - 1, pt.y);
		return pt;
	}

	else if (visited[pt.x][pt.y - 1] /*&& world->IsValidPosition(Point2D(pt.x, pt.y - 1))*/) // south
	{
		nextPt = Point2D(pt.x, pt.y - 1);
		return pt;
	}

	else if (visited[pt.x + 1][pt.y] /*&& world->IsValidPosition(Point2D(pt.x + 1, pt.y))*/) // west
	{
		nextPt = Point2D(pt.x + 1, pt.y);
		return pt;
	}

	return Point2D(INT_MAX, INT_MAX);
}
