#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "program.h"

int partition(std::vector<std::pair<int, int>> &vec, Program &program, int low, int high)
{
    int pivot = vec.at(high).first;
    int j = low - 1;

    for (int i = low; i <= high; i++)
    {
        if (vec.at(i).first < pivot)
        {
            j++;
            std::swap(vec.at(i), vec.at(j));
            program.sortingHelper(QUICKSORT_DELAY, {i, j});
        }
    }
    std::swap(vec.at(j + 1), vec.at(high));
    program.sortingHelper(QUICKSORT_DELAY, {j+1, high});
    return j + 1;
}

void quickSort(std::vector<std::pair<int, int>> &vec, Program &program, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(vec, program, low, high);

        quickSort(vec, program, low, pivot - 1);
        quickSort(vec, program, pivot + 1, high);
    }
}

#endif
