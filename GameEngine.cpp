//
//  Game.cpp
//  BombermanClient
//
//  Created by Amealky on 07/06/2018.
//  Copyright © 2018 Amealky. All rights reserved.
//

#include "GameEngine.hpp"


GameEngine::GameEngine(sf::RenderWindow* window, DrawingServer* drawingServer, PhysicsServer* physicsServer, IController* controller, NetworkManager* networkManager) {
    this->window = window;
    this->drawingServer = drawingServer;
    this->physicsServer = physicsServer;
    this->controller = controller;
    this->networkManager = networkManager;
    this->currentScreen = NULL;
    this->music = new Music();
    this->currentMusicPlayedPath = "";
}



GameEngine::~GameEngine() { 
    delete window;
    delete drawingServer;
    delete physicsServer;
    delete controller;
    delete networkManager;

    for(Screen* screen : screens) {
        delete screen;
    }
    screens.clear();

    delete music;
}


void GameEngine::runGameEngine() {
    Event event;

    //We start at showing the first screen in the list
    currentScreen = screens[0];
    currentScreen->launchScreen(this, {});

    //Game Loop
    while (window->isOpen()) {

        //Polling and Mapping Events
         while(window->pollEvent(event)) {
            MappedEvent mappedEvent = controller->mapEvent(event);
            if (mappedEvent.eventType == INPUT_EVENT::EXIT_PRESSED) {
                window->close();
            }
            else {
                currentScreen->handleInput(controller->mapEvent(event), this);
            }
         }


        //Manage network requests
        if(networkManager->isServer()) {
            currentScreen->handleNetworkClientsData(networkManager->readClients(), this);
        } else {
            currentScreen->handleNetworkServerData(networkManager->readServer(), this);
        }


        //Manage rendering update ( screen and gameEntities) and physics
        window->clear(Color(25, 25, 25));
        currentScreen->updateScreen(this);

        vector<GameEntity*> currentGameEntities = currentScreen->getGameEntities();
        for(GameEntity* gameEntity : currentGameEntities) {
            gameEntity->setNetworkManager(networkManager);
        }

        drawingServer->setGameEntities(currentGameEntities);
        drawingServer->draw(window, currentScreen->getUIView(), currentScreen->getGameView());

        physicsServer->setGameEntities(currentGameEntities);
        physicsServer->checkPhysicalCollisions();
        physicsServer->checkTriggerCollisions();

        window->display();
        //Then loop while window is open
    }
    
}

void GameEngine::goToScreen(string name) {
    goToScreen(name, {});
}

void GameEngine::goToScreen(string name, vector<string> datas) {
    for(Screen* screen : screens) {
        if(screen->getName() == name) {
            currentScreen->exitScreen(this);
            currentScreen = screen;
            currentScreen->launchScreen(this, datas);
        }
    }
}

void GameEngine::addScreen(Screen* screen) {
    for(Screen* existingScreen : screens) {
        if(existingScreen->getName() == screen->getName()) {
            throw runtime_error("You try to add screen that already exist : " + screen->getName());
        }
    }

    screens.push_back(screen);
}

void GameEngine::changeMusic(string musicPath) {
    if(musicPath != currentMusicPlayedPath) {
        music->openFromFile(musicPath);
        music->setVolume(15);
        music->setLoop(true);
        music->play();
        this->currentMusicPlayedPath = musicPath;
    }

}

NetworkManager* GameEngine::getNetworkManager() {
    return this->networkManager;
}

Music* GameEngine::getMusic() {
    return this->music;
}