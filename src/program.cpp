#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "program.h"

#include "bubblesort.h"
#include "mergesort.h"

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 200
#define AMOUNT_OF_BARS 200
#define BUBBLESORT_DELAY 10
#define MERGESORT_DELAY 25


Program::Program(const char* title, int xpos, int ypos, int w, int h, bool fullscreen)
{
    // Intialize SDL components
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw std::runtime_error("Could not initialize SDL.");
    window  = SDL_CreateWindow(title, xpos, ypos, w, h, fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
    if (!window) throw std::runtime_error("Could not initialize window.");
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) throw std::runtime_error("Could not initialize renderer.");
    isRunning = true;
    if (TTF_Init() != 0) throw std::runtime_error("Could not initialize TTF.");

    // Start screen button initialization

    bubbleSortButton = new Button(renderer, w/4.0f * 0, h/2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT);
    bubbleSortButton->setText("Bubble sort", 24);

    selectionSortButton = new Button(renderer, w/4.0f * 1, h/2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT);
    selectionSortButton->setText("Selection sort", 24);

    insertionSortButton = new Button(renderer, w/4.0f * 2, h/2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT);
    insertionSortButton->setText("Insertion sort", 24);

    mergeSortButton = new Button(renderer, w/4.0f * 3, h/2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT);
    mergeSortButton->setText("Merge sort", 24);

    this->w = w;
    this->h = h;

    // Sets the seed for the random number generator
    srand(time(NULL));

    generateNewValues();
}

Program::~Program()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void Program::render()
{
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (currentAlgorithm == NONE)
    {
        // Render start screen buttons
        bubbleSortButton->render();
        selectionSortButton->render();
        insertionSortButton->render();
        mergeSortButton->render();
    }
    else
        renderVectorBars();
    SDL_RenderPresent(renderer);
}

void Program::update()
{
    // Remove highlighting from all elements
    for (int i = 0; i < currVec.size(); i++)
        currVec.at(i).second = 0;
    if (currentAlgorithm == BUBBLE)
    {
        bubbleSort(currVec, *this, BUBBLESORT_DELAY);
    }
    if (currentAlgorithm == MERGE)
    {
        mergeSort(currVec, *this, MERGESORT_DELAY, 0, currVec.size() - 1);
        reset();
    }
}

void Program::renderVectorBars() const
{
    int w, h, rectW;
    SDL_GetWindowSize(window, &w, &h);
    rectW = w / (int)currVec.size();
    for (int i = 0; i < currVec.size(); i++)
    {
        // Select red if current element should be highlighted, else white
        if (currVec.at(i).second == 1)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        // Draw the bar
        SDL_Rect rect = {i * rectW, h - currVec.at(i).first, rectW, currVec.at(i).first};
        SDL_RenderFillRect(renderer, &rect);

        // Draw black outline to seperate the bars
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void Program::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            // Mouse button is pressed
            case SDL_MOUSEBUTTONUP:
                // Check if the mouse is currently on any buttons
                if (bubbleSortButton->mouseHover())
                    currentAlgorithm = BUBBLE;
                if (selectionSortButton->mouseHover())
                    currentAlgorithm = SELECTION;
                if (insertionSortButton->mouseHover())
                    currentAlgorithm = INSERTION;
                if (mergeSortButton->mouseHover())
                    currentAlgorithm = MERGE;
                break;
            default:
                break;
        }
    }
}

void Program::generateNewValues()
{
    currVec.clear();
    // Create AMOUNT_OF_BARS random elements of value between 0 and the screen height
    for  (int i = 0; i < AMOUNT_OF_BARS; i++)
        currVec.push_back(std::make_pair(rand() % (h - 5) + 5, 0));
}

void Program::reset()
{
    currentAlgorithm = NONE;
    generateNewValues();
}