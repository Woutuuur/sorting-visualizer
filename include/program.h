#ifndef PROGRAM_H
#define PROGRAM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <stack>
#include "button.h"

enum algorithm {NONE, BUBBLE, INSERTION, SELECTION, MERGE};

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

        std::vector<int> vec;
        std::vector<std::pair<int, int>> currVec;

        int w, h;
        
        void generateNewValues();
};

#endif