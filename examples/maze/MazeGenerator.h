#ifndef MOBAGEN_MAZEGENERATOR_H
#define MOBAGEN_MAZEGENERATOR_H

#include "MazeGeneratorBase.h"
#include <random>
#include <ctime>

// please do not use this one anymore. Move your code to the specific implementation.
// I am going to rename this interface soon to be a naive implementation.
class MazeGenerator : public MazeGeneratorBase
{
private:
	std::mt19937 random = std::mt19937(std::time(nullptr));

public:
	MazeGenerator();
	// todo: in order to step work properly, you have to store your current exploration status in the MazeGenerator members
	// Steps should return true if it made changes in the world
	bool Step(World* world);
	// Clears and resets all data from the generator
	void Clear(World* world);

	void InitRandom(int seed);
	int Random(int bounds);

};

#endif
