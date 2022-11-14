#include "RandomGenerator.h"
#include "../Noise.h"
#include "../PerlinNoise.hpp"
#include <iostream>
// do not use this one to your assignment. this is my sample generator
std::vector<Color32> RandomScenarioGenerator::Generate(int sideSize, float displacement)
{
    std::vector<Color32> colors;
    //   create your own function for noise generation
    siv::BasicPerlinNoise<float> noise;
    noise.reseed(1337);
    //  Noise noise(1337, 1024,0,255);
    for (int l = 0; l < sideSize; l++)
    {
        for (int c = 0; c < sideSize; c++)
        {
            // 1 - (1-nx�) * (1-ny�)
            float nx = 2 * (float)c / (float)sideSize - 1;
            float ny = 2 * (float)l / (float)sideSize - 1;
            float dist = 1 - ((1 - (nx * nx)) * (1 - (ny * ny)));

            float rgb = (abs(noise.octave3D(c / 50.0, l / 50.0, displacement, 5)) - abs(noise.octave3D(c / 150.0, l / 150.0, displacement, 20))) * 255;
            
            rgb = (rgb + ((1 - dist) * 255)) / 2;

            float r, g, b;

            if (rgb < 100)
            {
                r = 0;
                g = 0;
                b = abs(rgb - 200);
            }
            else
            {
                r = 0;
                g = abs(rgb - 200);
                b = 0;
            }
            
            colors.emplace_back(r, g, b);
            //      double color = noise.noise(c/50.0,l/50.0);
            //      colors.emplace_back(color,color,color);
        }
    }
    std::cout << colors.size() << std::endl;
    return colors;
}
std::string RandomScenarioGenerator::GetName() { return "EXAMPLE"; }
