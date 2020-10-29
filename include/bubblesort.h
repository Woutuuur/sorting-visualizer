#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <vector>
#include <utility>
#include "program.h"

void bubbleSort(std::vector<std::pair<int, int>> &vec, Program &program)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec.size() - i - 1; j++)
        {
            if (vec.at(j).first > vec.at(j + 1).first)
            {
                program.sortingHelper(BUBBLESORT_DELAY, {j, j+1});
                std::swap(vec.at(j), vec.at(j + 1));
            }
        }
    }
}

#endif