//
//  main.cpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Utils.hpp"
#include "GameEngine.hpp"

#include "Servers/DrawingServer.hpp"
#include "Servers/PhysicsServer.hpp"

#include "Controls/KeyboardController.hpp"

#include "Screens/StartScreen.hpp"
#include "Screens/ConnectionScreen.hpp"
#include "Screens/LobbyScreen.hpp"
#include "Screens/MapSelectionScreen.hpp"
#include "Screens/ArenaScreen.hpp"


using namespace sf;

int main(int argc, char* argv[])
{
    setExecutablePath(argv[0]);

    //Creation of the game window
    RenderWindow* window = new RenderWindow(VideoMode(800, 600), "Bon Beurre Man");
    Image icon;
    string iconPath = getAssetDirectory() +"Images/icon.png";
    if (!icon.loadFromFile(iconPath)) {
          throw runtime_error("Error while loading app icon : " + iconPath);
    }
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window->setKeyRepeatEnabled(false);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);

    //Initilisation of the differents servers
    DrawingServer* drawingServer = new DrawingServer(4);
    PhysicsServer* physicsServer = new PhysicsServer();
    
    //Initialisation of a Controller method ( could be enhance by using a list of IController into the Game Engine)
    IController* ctrl = new KeyboardController();
    
    //Initialisation of the network manager
    NetworkManager* networkManager = new NetworkManager(8002);
    networkManager->setMaxClients(3);

    //Initialisation of the game engine with all the require Servers, controlers, manager and with a main window
    //Cause for now this engine only manage a single window
    GameEngine* gameEngine = new GameEngine(window, drawingServer, physicsServer, ctrl, networkManager);

    //Initialisation of all the different screen fo our Bomberman like game 
    StartScreen* startScreen = new StartScreen("StartScreen", window);
    ConnectionScreen* connectionScreen = new ConnectionScreen("ConnectionScreen", window);
    LobbyScreen* lobbyScreen = new LobbyScreen("LobbyScreen", window);
    MapSelectionScreen* mapSelectionScreen = new MapSelectionScreen("MapSelectionScreen", window);
    ArenaScreen* arenaScreen = new ArenaScreen("ArenaScreen", window);
    gameEngine->addScreen(startScreen);
    gameEngine->addScreen(connectionScreen);
    gameEngine->addScreen(lobbyScreen);
    gameEngine->addScreen(mapSelectionScreen);
    gameEngine->addScreen(arenaScreen);
    
    
    //Start the engine !
    gameEngine->runGameEngine();

    //Before we leave we destroy the GameEngine 
    delete gameEngine;

    
    return EXIT_SUCCESS;
}
