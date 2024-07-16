//
//  ConnectionScreen.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef ConnectionScreen_hpp
#define ConnectionScreen_hpp

#include <SFML/Graphics.hpp>

#include "Screen.hpp"
#include "../Network/NetworkManager.hpp"


class ConnectionScreen : public Screen {

    public: 
        ConnectionScreen(string name, RenderWindow* window);
        ~ConnectionScreen();

        //Core
        void launchScreen(GameEngine* engine, vector<string> datas) override;
        void setupUIView() override;
        void handleInput(MappedEvent inputEvent, GameEngine* engine) override;

    private:
        //Core
        void generateTitleText();
        void generateIPEditText();
        void generatePortText(string portValue);
        void generateExitText();
        void generateConnectText();
        void generateLoadingStatus();
        bool tryConnection(NetworkManager* networkManager);

};

#endif