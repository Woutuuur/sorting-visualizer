#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include "program.h"
#include <iostream>
#include <algorithm> 

void bucketSort(std::vector<std::pair<int, int>> &vec, Program &program)
{
    std::vector<std::vector<int>> buckets(vec.size());

    // Works because all values in the vector are between 0 and screen height (so never negative)
    float maxVal = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec.at(i).first > maxVal)
            maxVal = vec.at(i).first;
    }
    for (int i = 0; i < vec.size(); i++)
    {
        int bucketIndex = std::floor((buckets.size() - 1) * (vec.at(i).first / maxVal));
        buckets.at(bucketIndex).push_back(vec.at(i).first);
        program.sortingHelper(BUCKETSORT_DELAY, {i});
    }

    int k = 0;
    for (int i = 0; i < buckets.size(); i++)
    {
        std::sort(buckets.at(i).begin(), buckets.at(i).end());
        for (int j = 0; j < buckets.at(i).size(); j++)
        {
            program.sortingHelper(BUCKETSORT_DELAY, {k});
            vec.at(k++).first = buckets.at(i).at(j);
        }
    }
}

#endif
