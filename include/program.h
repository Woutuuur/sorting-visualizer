#ifndef PROGRAM_H
#define PROGRAM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <stack>
#include "button.h"

#define BUBBLESORT_DELAY 2
#define INSERTIONSORT_DELAY 2
#define SELECTIONSORT_DELAY 2
#define BUCKETSORT_DELAY 25
#define MERGESORT_DELAY 25
#define QUICKSORT_DELAY 25

#define BUTTON_HEIGHT 200
#define AMOUNT_OF_BARS 200

enum algorithm {NONE, BUBBLE, INSERTION, SELECTION, MERGE, QUICK, BUCKET};

class Program
{
    public:
        Program();
        Program(const char* title, int xpos, int ypos, int w, int h, bool fullscreen);
        ~Program();

        void handleEvents();
        void render();
        void update();

        void renderVectorBars() const;
        void setCurrentAlgorihtm (algorithm algorithm) {this->currentAlgorithm = algorithm;}
        void sortingHelper(int delay, std::vector<int> toHighlight);
        
        bool running() const {return isRunning;}
        void reset();
    private:
        bool isRunning;
        algorithm currentAlgorithm = NONE;
        SDL_Window* window;
        SDL_Renderer* renderer;

        Button* bubbleSortButton;
        Button* insertionSortButton;
        Button* selectionSortButton;
        Button* mergeSortButton;
        Button* quickSortButton;
        Button* bucketSortButton;

        std::vector<std::pair<int, int>> currVec;

        int w, h;
        void generateNewValues();
};

#endif
