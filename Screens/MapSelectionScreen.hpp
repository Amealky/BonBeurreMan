//
//  MapSelectionScreen.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef MapSelectionScreen_hpp
#define MapSelectionScreen_hpp

#include <SFML/Graphics.hpp>

#include "Screen.hpp"
#include "../Utils.hpp"
#include "../Entities/Map.hpp"

class MapSelectionScreen : public Screen {

    public:
        MapSelectionScreen(string name, RenderWindow* window);
        ~MapSelectionScreen();
        //Core
        void launchScreen(GameEngine* engine, vector<string> datas) override;
        void setupUIView() override;
        void setupGameView() override;
        void updateScreen(GameEngine* engine) override;
        void handleInput(MappedEvent inputEvent, GameEngine* engine) override;
        void handleNetworkServerData(vector<string> datas, GameEngine* engine) override;

    private:
        //Core
        void generateTitleText();
        void generateArrows();
        void generateExitText();
        void generateStartText();
        void showArrows();
        void hideLeftArrow();
        void hideRightArrow();
        void goLeft();
        void goRight();
        void sendNewCurrentIndex(NetworkManager* networkManager);

        int currentMapIndex = 0;
};


#endif