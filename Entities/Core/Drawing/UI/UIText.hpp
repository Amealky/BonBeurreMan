//
//  UIText.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef UIText_hpp
#define UIText_hpp

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class UIText {

    public:
        UIText(string textValue, int characterSize, Color textColor, string fontPath);
        ~UIText();

        //Core
        void load();
        void draw(RenderWindow* window, int posX, int posY); 

        //Getter
        Text* getText();
        string getTextValue();
        Font* getFont();
        string getFontPath();

        //Setter
        void setText(Text* text);
        void setTextValue(string textValue);
        void setFont(Font* font);
        void setFontPath(string fontPath);
        void setColor(Color color);



    private:
        Text* text;
        Font* font;
        string fontPath;


};


#endif