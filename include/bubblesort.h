#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <vector>
#include <utility>
#include "program.h"

void bubbleSort(std::vector<std::pair<int, int>> &vec, Program &program, const int delay)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec.size() - i - 1; j++)
        {
            if (vec.at(j).first > vec.at(j + 1).first)
            {
                program.handleEvents();
                if (!program.running())
                    return;

                // Get rid of any previous highlighting
                for (int i = 0; i < vec.size(); i++)
                    vec.at(i).second = 0;

                vec.at(j).second = 1;
                vec.at(j+1).second = 1;

                std::swap(vec.at(j), vec.at(j + 1));
                program.render();
                SDL_Delay(delay);
            }
        }
    }
    program.reset();
}

#endif