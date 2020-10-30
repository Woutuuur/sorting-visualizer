#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include "program.h"
#include <iostream>
#include <algorithm>

void bucketSort(std::vector<std::pair<int, int>> &vec, Program &program)
{
    std::vector<std::vector<int>> buckets(vec.size());
    std::vector<std::vector<int>> realIndexes(vec.size());

    // Since the elements are in range 0 - screen height, no need to handle negative values
    float maxVal = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec.at(i).first > maxVal)
            maxVal = vec.at(i).first;
    }
    // Put all elements in correct bucket
    for (int i = 0; i < vec.size(); i++)
    {
        int bucketIndex = std::floor((buckets.size() - 1) * (vec.at(i).first / maxVal));
        buckets.at(bucketIndex).push_back(vec.at(i).first);
        // Keep track of the indexes of the element that are now in buckets
        realIndexes.at(bucketIndex).push_back(i);
        // Visualize the element that is being put in a bucket
        program.sortingHelper(BUCKETSORT_DELAY, {i});
    }
    
    for (int i = 0; i < buckets.size(); i++)
    {
        std::vector<int> v2, v3;
        v2 = std::vector<int>(buckets.at(i).begin(), buckets.at(i).end());
        // Indexes of the elements in the original vector of the items in the bucket i
        v3 = std::vector<int>(realIndexes.at(i).begin(), realIndexes.at(i).end());
        // Visualize the elements that are in the bucket that is currently being sorted (at their original index)
        program.sortingHelper(BUCKETSORT_DELAY, v3);
        // Sort buckets using insertion sort
        insertionSort(v2, program);
    }

    // Place items back in original vector
    int k = 0;
    for (int i = 0; i < buckets.size(); i++)
    {
        for (int j = 0; j < buckets.at(i).size(); j++)
        {
            // Visualize the element that is being put back into the vector
            program.sortingHelper(BUCKETSORT_DELAY, {k});
            vec.at(k++).first = buckets.at(i).at(j);
        }
    }
}

#endif
