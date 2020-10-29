#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <utility>
#include <ctime>
#include <iomanip>
#include "program.h"

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 600

int main()
{
    try
    {
        Program* program = new Program("Sorting visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
        while (program->running())
        {
            program->handleEvents();
            program->update();
            program->render();
        }
        delete program;
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}