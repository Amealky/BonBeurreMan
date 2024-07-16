//
//  UIEditText.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//


#ifndef UIEditText_hpp
#define UIEditText_hpp


#include <SFML/Graphics.hpp>
#include "UIText.hpp"

using namespace std;
using namespace sf;

class UIEditText {

    public:
        UIEditText(float sizeX, float sizeY, int maxChar, int characterSize, Color textColor, string fontPath);
        ~UIEditText();

        //Core
        void load();
        void draw(RenderWindow* window, int posX, int posY); 

        //Getter
        float getSizeX();
        float getSizeY();
        float getMarginX();
        float getMaxChar();
        RectangleShape* getBackground();
        UIText* getUIText();

        //Setter
        void setSizeX(float sizeX);
        void setSizeY(float sizeY);
        void setMarginX(float marginX);
        void setMaxChar(float maxChar);
        void setBackgroundColor(Color color);
        void addChar(char c);
        void removeChar();


    private:
        float sizeX;
        float sizeY;
        float marginX;
        float maxChar;
        RectangleShape* background;
        UIText* uiText;


};


#endif