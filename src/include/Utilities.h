#ifndef UTILITIES_H
#define UTILITIES_H

#include <utility>
#include <map>

#include <random>
#include <chrono>
#include <vector>

namespace PersonalBestScore
{
    extern std::map< std::tuple<int, int, int>, float > BestScore;

    void LoadData();
    bool UpdateData(int rows, int cols, int bombs, float score);
    float GetPersonalBest(int rows, int cols, int bombs);
}

namespace Random 
{
    extern std::mt19937 mt;

    int randInt(int l_bound = INT_MIN, int r_bound = INT_MAX);

    template <typename T>
    void shuffleList(std::vector<T>& _v)
    {
        shuffle(_v.begin(), _v.end(), mt);
    }
}

bool IsSaveFileValid(const char* filename);

#endif  