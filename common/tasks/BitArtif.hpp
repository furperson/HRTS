#pragma once 

#include <vector>
#include <array>

struct Sample
{
        std::array<bool, 64> sampleData;
};


struct BitArtef
{
        std::vector<Sample> rawData;
};
