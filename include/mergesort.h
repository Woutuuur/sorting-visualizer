#ifndef MERGESORT_H
#define MERGESORT_H

#include "program.h"

void merge(std::vector<std::pair<int, int>> &vec, Program &program, int begin, int mid, int end)
{
    int len1 = mid - begin + 1;
    int len2 = end - mid;

    std::vector<int> toHighlight;

    std::vector<std::pair<int, int>> left(len1);
    std::vector<std::pair<int, int>> right(len2);

    for (int i = 0; i < len1; i++)
        left.at(i).first = vec.at(begin + i).first;
    for (int i = 0; i < len2; i++)
        right.at(i).first = vec.at(mid + i + 1).first;

    int i = 0, j = 0;
    int k = begin;

    toHighlight.push_back(k);
    while (i < len1 && j < len2)
    {
        if (left.at(i).first <= right.at(j).first)
        {
            vec.at(k).first = left.at(i).first;
            toHighlight.push_back(begin + i);
            i++;
        }
        else
        {
            vec.at(k).first = right.at(j).first;
            toHighlight.push_back(mid + j + 1);
            j++;
        }
        program.sortingHelper(MERGESORT_DELAY, toHighlight);
        k++;
    }
    while (i < len1)
    {
        vec.at(k).first = left.at(i).first;
        toHighlight.push_back(begin + i);
        i++;
        k++;
        program.sortingHelper(MERGESORT_DELAY, toHighlight);
    }
    while (j < len2)
    {
        vec.at(k).first = right.at(j).first;
        toHighlight.push_back(mid + j + 1);
        j++;
        k++;
        program.sortingHelper(MERGESORT_DELAY, toHighlight);
    }
}

void mergeSort(std::vector<std::pair<int, int>> &vec, Program &program, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(vec, program, left, mid);
        mergeSort(vec, program, mid + 1, right);

        merge(vec, program, left, mid, right);
    }
}

#endif