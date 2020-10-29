#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "program.h"

int partition(std::vector<std::pair<int, int>> &vec, Program &program, const int delay, int low, int high)
{

    int pivot = vec.at(high).first;
    int j = low - 1;

    for (int i = low; i <= high; i++)
    {
        if (vec.at(i).first < pivot)
        {
            j++;
            std::swap(vec.at(i), vec.at(j));
            program.sortingHelper(delay, {i, j});
        }
    }
    std::swap(vec.at(j + 1), vec.at(high));
    program.sortingHelper(delay, {j+1, high});
    return j + 1;
}

void quickSort(std::vector<std::pair<int, int>> &vec, Program &program, const int delay, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(vec, program, delay, low, high);

        quickSort(vec, program, delay, low, pivot - 1);
        quickSort(vec, program, delay, pivot + 1, high);
    }
}

#endif