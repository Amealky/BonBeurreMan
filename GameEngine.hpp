//
//  GameEngine.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef GameEngine_hpp
#define GameEngine_hpp

#include <stdio.h>
#include <thread>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Servers/DrawingServer.hpp"
#include "Servers/PhysicsServer.hpp"
#include "Screens/Screen.hpp"
#include "Controls/IController.hpp"
#include "Network/NetworkManager.hpp"

using namespace std;
using namespace sf;


class Screen;

class GameEngine {
  
public:

    GameEngine(RenderWindow* window, DrawingServer* drawingServer, PhysicsServer* physicsServer, IController* controller, NetworkManager* networkManager);
    ~GameEngine();

    //Core
    void runGameEngine();
    void goToScreen(string name);
    void goToScreen(string name, vector<string> datas);    
    void addScreen(Screen* screen);
    void changeMusic(string musicPath);

    //Getter
    NetworkManager* getNetworkManager();
    Music* getMusic();
    
    
    
private:
    RenderWindow* window;
    DrawingServer* drawingServer;
    PhysicsServer* physicsServer;
    IController* controller;
    NetworkManager* networkManager;

    vector<Screen*> screens;
    Screen* currentScreen;

    Music* music;
    string currentMusicPlayedPath;
    
};


#endif
