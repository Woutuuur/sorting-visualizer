#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "program.h"

void insertionSort(std::vector<std::pair<int, int>> &vec, Program &program, const int delay)
{
    int key, j;
    for (int i = 1; i < vec.size(); i++)
    {
        j = i;
        key = vec.at(i).first;
        while (j > 0 && vec.at(j - 1).first > key)
        {
            vec.at(j).first = vec.at(j - 1).first;
            program.sortingHelper(delay, {j, j - 1});
            j--;
        }
        vec.at(j).first = key;
    }
}

#endif