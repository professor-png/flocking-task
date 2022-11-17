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

            if (rgb < 100) // ocean
            {
                r = 0;
                g = 0;
                b = rgb + 100;
                if (b < 120)
                    b = rgb + 120;
                
                if (b > 200)
                    b = (rgb / 10) + 200;
            }
            else if (rgb < 110)
            {
                r = rgb + 70;
                g = rgb + 70;
                b = 0;
            }
            else if (rgb < 180) // forest
            {
                r = 0;
                b = 0;
                g = rgb;//abs(rgb - 200);

                if (g > 150)
                    g = 180 - (rgb - 100);
                
            }
            else
            {
                r = rgb - 50;
                g = rgb - 50;
                b = rgb - 50;
            }
            
            //colors.emplace_back(rgb, rgb, rgb);
            colors.emplace_back(r, g, b);
            //      double color = noise.noise(c/50.0,l/50.0);
            //      colors.emplace_back(color,color,color);
        }
    }
    std::cout << colors.size() << std::endl;
    return colors;
}
std::string RandomScenarioGenerator::GetName() { return "EXAMPLE"; }
