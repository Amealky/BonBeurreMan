//
//  LobbyScreen.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef LobbyScreen_hpp
#define LobbyScreen_hpp

#include <SFML/Graphics.hpp>

#include "Screen.hpp"

class LobbyScreen : public Screen {

    public:
        LobbyScreen(string name, RenderWindow* window);
        ~LobbyScreen();

        //Core
        void launchScreen(GameEngine* engine, vector<string> datas) override;
        void setupUIView() override;
        void updateScreen(GameEngine* engine) override;
        void handleInput(MappedEvent inputEvent, GameEngine* engine) override;
        void handleNetworkServerData(vector<string> datas, GameEngine* engine) override;

    private:
        //Core
        void generateTitleText();
        void generateExitText();
        void generateStartText();
        void generateEmptySlotText(int slotCounts);
        void generateFarmersSprites(int slotCounts);
        void showFarmer(int number);
        void hideFarmer(int number);
        
        vector<Vector2f> slotPositions;
};

#endif