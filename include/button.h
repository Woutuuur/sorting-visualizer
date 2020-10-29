#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button
{
    public:
        Button(SDL_Renderer* renderer, const int x, const int y, const int w, const int h);
        ~Button();
        void render();
        void setBackgroundColor(const int r, const int g, const int b);
        void setTextColor(const int r, const int g, const int b);
        void setText(std::string text);
        void setText(std::string text, const int fontSize);
        void setFontSize(const unsigned int fontSize);
        void setFont(std::string fontDir);
        bool mouseHover() const;
    private:
        SDL_Rect* buttonRect;
        SDL_Renderer *renderer;
        SDL_Color backgroundColor = {255, 255, 255, 255};

        // Text components
        std::string text = "Button";
        std::string fontDir = "./res/FreeSans.ttf";
        int fontSize = 12;
        SDL_Color textColor = {0, 0, 0, 255};
        TTF_Font* font;
        void setFont();

        void renderText() const;
        
};