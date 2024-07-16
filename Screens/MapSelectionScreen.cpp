#include "MapSelectionScreen.hpp"

MapSelectionScreen::MapSelectionScreen(string name, RenderWindow* window) : Screen(name, window) {}

MapSelectionScreen::~MapSelectionScreen() {
    Screen::~Screen();
}

void MapSelectionScreen::launchScreen(GameEngine* engine, vector<string> datas) {
    vector<string> mapFiles = listFilesFrom(getAssetDirectory() +"Maps/", "tmap");

    for(int i = 0; i < mapFiles.size(); i++) {
        Map* map = new Map("Map" + to_string(i), mapFiles[i], getAssetDirectory() +"Images/Barn/BarnTileset.png");
        map->load();
        if(i == 0) {
            map->setVisible(true);
        } else {
            map->setVisible(false);
        }
        gameEntities.push_back(map);
    }

    Screen::launchScreen(engine, datas);

    generateTitleText();

    if(mapFiles.size() > 1) {
        generateArrows();
    }
    generateExitText();
    if(engine->getNetworkManager()->isServer()) {
        generateStartText();
    }
}

void MapSelectionScreen::setupUIView() {
    Screen::setupUIView();
    
    View* uiView = new View();
    uiView->setSize(window->getSize().x, window->getSize().y);
    uiView->setCenter(window->getSize().x / 2, window->getSize().y / 2);
    this->setUIView(uiView);
}

void MapSelectionScreen::setupGameView() {
    vector<Map*> maps = getGameEntitiesOfType<Map>();
    if(maps.size() > 0) {
        Map* map = maps[currentMapIndex];
        Screen::setupGameView();

        View* gameView = new View();
        gameView->setSize(map->getWidthInPixel(), map->getHeightinPixel());
        gameView->setCenter(map->getWidthInPixel()/2, map->getHeightinPixel()/2);


        float xPos = (window->getSize().x - gameView->getSize().x) / 2;
        float yPos = (window->getSize().y - gameView->getSize().y) / 2;
        gameView->setViewport(sf::FloatRect(xPos / window->getSize().x,
                            yPos / window->getSize().y, 
                            gameView->getSize().x / window->getSize().x, 
                            gameView->getSize().y / window->getSize().y));
        this->setGameView(gameView);
    }
}

void MapSelectionScreen::updateScreen(GameEngine* engine) {
    vector<Map*> maps = getGameEntitiesOfType<Map>();
    showArrows();

    if(currentMapIndex == 0) {
        hideLeftArrow();
    }

    if(currentMapIndex == maps.size()-1) {
        hideRightArrow();
    }

    for(int i = 0; i < maps.size(); i++) {
        if(i == currentMapIndex) {
            maps[i]->setVisible(true);
            continue;
        }

        maps[i]->setVisible(false);
    }

}

void MapSelectionScreen::handleInput(MappedEvent inputEvent, GameEngine* engine) {
    NetworkManager* networkManager = engine->getNetworkManager();

    switch(inputEvent.eventType) {
        case INPUT_EVENT::LEFT_PRESSED: 
            goLeft();
            sendNewCurrentIndex(networkManager);
            break;
        case INPUT_EVENT::RIGHT_PRESSED: 
            goRight();
            sendNewCurrentIndex(networkManager);
            break;
        case INPUT_EVENT::ENTER_PRESSED:
            if(networkManager->isServer()) {
                vector<string> networkDatas;
                vector<string> localDatas;
                networkDatas.push_back("GO_TO");
                networkDatas.push_back("ArenaScreen");
                networkDatas.push_back(to_string(currentMapIndex));
                localDatas.push_back(to_string(currentMapIndex));
                for (auto& pair : networkManager->getClients()) {
                    networkDatas.push_back(to_string(pair.first));
                    localDatas.push_back(to_string(pair.first));
                }
                networkManager->sendToClients(networkDatas);
                engine->goToScreen("ArenaScreen", localDatas);
            }
            break;
        case INPUT_EVENT::ESCAPE_PRESSED: {
            if(networkManager->isServer()) {
                vector<string> datas;
                datas.push_back("GO_TO");
                datas.push_back("LobbyScreen");
                for (auto& pair : networkManager->getClients()) {
                    datas.push_back(to_string(pair.first));
                }
                networkManager->sendToClients(datas);
                engine->goToScreen("LobbyScreen");
            } else {
                networkManager->disconnect();
                engine->goToScreen("ConnectionScreen");
            }
            break;
        }
        default:
            break;
    }
}

void MapSelectionScreen::handleNetworkServerData(vector<string> datas, GameEngine* engine) {
    Screen::handleNetworkServerData(datas, engine);

    if(datas.size() > 0) {
        if(datas[0] == "CURRENT_MAP_INDEX") {
            currentMapIndex = stoi(datas[1]);
            setupGameView();
        }
    }
}

void MapSelectionScreen::generateTitleText() {
    GameEntity* titleTextGameEntity = createUITextGameEntity("MapSelectionTitle", "Map Selection", 30, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf"); 
    titleTextGameEntity->setPosX(window->getSize().x/2 - titleTextGameEntity->getUIText()->getText()->getLocalBounds().width/2);
    titleTextGameEntity->setPosY(30);
    gameEntities.push_back(titleTextGameEntity);
}

void MapSelectionScreen::generateArrows() {
    GameEntity* leftArrowGameEntity = createUITextGameEntity("LeftArrow", "<=", 50, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf"); 
    leftArrowGameEntity->setPosX(10);
    leftArrowGameEntity->setPosY(window->getSize().y/2);
    gameEntities.push_back(leftArrowGameEntity);

    GameEntity* rightArrowGameEntity = createUITextGameEntity("RightArrow", "=>", 50, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf"); 
    rightArrowGameEntity->setPosX(window->getSize().x - 10 - rightArrowGameEntity->getUIText()->getText()->getLocalBounds().width);
    rightArrowGameEntity->setPosY(window->getSize().y/2);
    gameEntities.push_back(rightArrowGameEntity);
}

void MapSelectionScreen::generateExitText() {
    GameEntity* exitTextGameEntity = createUITextGameEntity("ExitText", "ESC to go back", 15, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf"); 
    exitTextGameEntity->setPosX(10);
    exitTextGameEntity->setPosY(window->getSize().y - 45);
    gameEntities.push_back(exitTextGameEntity);
}

void MapSelectionScreen::generateStartText() {
    GameEntity* startTextGameEntity = createUITextGameEntity("StartText", "ENTER to start", 15, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf");
    startTextGameEntity->setPosX(window->getSize().x - startTextGameEntity->getUIText()->getText()->getLocalBounds().width - 10);
    startTextGameEntity->setPosY(window->getSize().y - 45);
    gameEntities.push_back(startTextGameEntity);
}

void MapSelectionScreen::showArrows() {
    getGameEntitiesByName("LeftArrow")[0]->setVisible(true);
    getGameEntitiesByName("RightArrow")[0]->setVisible(true);
}

void MapSelectionScreen::hideLeftArrow() {
     getGameEntitiesByName("LeftArrow")[0]->setVisible(false);
}

void MapSelectionScreen::hideRightArrow() {
     getGameEntitiesByName("RightArrow")[0]->setVisible(false);
}

void MapSelectionScreen::goLeft() {
    if(currentMapIndex > 0) {
        currentMapIndex--;
        setupGameView();
    }
}

void MapSelectionScreen::goRight() {
    if(currentMapIndex < getGameEntitiesOfType<Map>().size()-1) {
        currentMapIndex++;
        setupGameView();
    }
}

void MapSelectionScreen::sendNewCurrentIndex(NetworkManager* networkManager) {
    vector<string> datas;
    datas.push_back("CURRENT_MAP_INDEX");
    datas.push_back(to_string(this->currentMapIndex));
    networkManager->sendToClients(datas);
}