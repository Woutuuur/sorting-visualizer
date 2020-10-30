#include <stdexcept>
#include <string>
#include "button.h"

Button::Button(SDL_Renderer* renderer, const int x, const int y, const int w, const int h)
{
    buttonRect = new SDL_Rect();
    buttonRect->x = x;
    buttonRect->y = y;
    buttonRect->w = w;
    buttonRect->h = h;
    this->renderer = renderer;
    font = TTF_OpenFont(fontDir.c_str(), fontSize);
}

Button::~Button()
{
    delete buttonRect;
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
}

void Button::setBackgroundColor(const int r, const int g, const int b)
{
    backgroundColor = {(Uint8)r, (Uint8)g, (Uint8)b, 255};
}

void Button::setTextColor(const int r, const int g, const int b)
{
    textColor = {(Uint8)r, (Uint8)g, (Uint8)b, 255};
}

bool Button::mouseHover() const
{
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse,&yMouse);
    return xMouse < buttonRect->x + buttonRect->w && xMouse > buttonRect->x && yMouse < buttonRect->y + buttonRect->h && yMouse > buttonRect->y;
}

void Button::render()
{
    if (mouseHover())
        SDL_SetRenderDrawColor(renderer, backgroundColor.r / 2, backgroundColor.g / 2, backgroundColor.b / 2, backgroundColor.a);
    else
        SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, buttonRect);
    renderText();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, buttonRect);
}

void Button::setText(std::string text)
{
    this->text = text;
}

void Button::setText(std::string text, const int fontSize)
{
    setText(text);
    setFontSize(fontSize);
}

void Button::renderText() const
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int textW, textH;
    TTF_SizeText(font, text.c_str(), &textW, &textH);
    // Centers text in middle of button
    SDL_Rect textRect = {buttonRect->x + (buttonRect->w - textW) / 2, buttonRect->y + (buttonRect->h - textH) / 2, textW, textH};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
void Button::setFont(std::string fontDir)
{
    this->fontDir = fontDir;
    setFont();
}

void Button::setFont()
{
    TTF_CloseFont(font);
    font = TTF_OpenFont(fontDir.c_str(), fontSize);
}

void Button::setFontSize(const unsigned int fontSize)
{
    this->fontSize = fontSize;
    setFont();
}
