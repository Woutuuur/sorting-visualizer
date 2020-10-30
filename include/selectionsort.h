#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include <utility>
#include "program.h"

void selectionSort(std::vector<std::pair<int, int>> &vec, Program &program)
{
    int iMin;
    for (int i = 0; i < vec.size(); i++)
    {
        iMin = i;
        for (int j = i + 1; j < vec.size(); j++)
        {
            if (vec.at(iMin).first > vec.at(j).first)
                iMin = j;
            program.sortingHelper(SELECTIONSORT_DELAY, {i, iMin, j});
        }
        std::swap(vec.at(i), vec.at(iMin));
    }
}

#endif