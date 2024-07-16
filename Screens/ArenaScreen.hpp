//
//  ArenaScreen.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef ArenaScreen_hpp
#define ArenaScreen_hpp

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Screen.hpp"

#include "../Entities/Player.hpp"
#include "../Entities/Map.hpp"

class ArenaScreen : public Screen {

    public: 
        ArenaScreen(string name, RenderWindow* window);
        ~ArenaScreen();

        //Core
        void launchScreen(GameEngine* engine, vector<string> datas) override;
        void setupUIView() override;
        void setupGameView() override;
        void updateScreen(GameEngine* engine) override;
        void handleInput(MappedEvent inputEvent, GameEngine* engine) override;
        void handleNetworkClientsData(unordered_map<string, vector<string>> datas, GameEngine* engine) override;
        void handleNetworkServerData(vector<string> datas, GameEngine* engine);
        void exitScreen(GameEngine* engine) override;
        
    private:
        //Core
        void generateMap(int mapNumber);
        Bomb* generateBasicBomb();
        void generatePlayers(vector<string> clientIds);
        void generateWinMessage();
        void generateExitText();
        bool checkGameIsDone();
        void showWinMessage();
        void showExitText();
        void hideEndGameUI();
        void putBomb(int playerId);

        bool gameIsDone;
    

};
#endif 