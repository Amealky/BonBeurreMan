//
//  StartScreen.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef StartScreen_hpp
#define StartScreen_hpp

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Screen.hpp"

class StartScreen : public Screen {

    public: 
        StartScreen(string name, RenderWindow* window);
        ~StartScreen();

        //Core
        void launchScreen(GameEngine* engine, vector<string> datas) override;
        void setupUIView() override;
        void updateScreen(GameEngine* engine) override;
        void handleInput(MappedEvent inputEvent, GameEngine* engine) override;

    private:
        //Core
        void generateBackground();
        void generateMenuItemsText();

        vector<string> menuItems;
        int itemSelected;

};
#endif 