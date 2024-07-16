#include "LobbyScreen.hpp"

LobbyScreen::LobbyScreen(string name, RenderWindow* window) : Screen(name, window) {}

LobbyScreen::~LobbyScreen() {
    Screen::~Screen();
}

void LobbyScreen::launchScreen(GameEngine* engine, vector<string> datas) {
    Screen::launchScreen(engine, datas);

    int slotCounts = engine->getNetworkManager()->getMaxClients()+1;

    float xPos = (window->getSize().x) / slotCounts;
    float yPos = window->getSize().y / 2;
    for(int i = 0; i < slotCounts; i++) {
        float slotXPos = i * xPos + xPos/2;
        float slotYPos =  yPos;
        slotPositions.push_back({slotXPos, slotYPos});
    }

    generateTitleText();
    generateExitText();
    if(engine->getNetworkManager()->isServer()) {
        generateStartText();
    }
    generateEmptySlotText(slotCounts);
    generateFarmersSprites(slotCounts);

    if(!engine->getNetworkManager()->isServer()) {
        for(int i = 1; i < engine->getNetworkManager()->getMaxClients()+1; i++) {
            hideFarmer(i);
        }

        for(int i = 0; i < datas.size(); i++) {
            showFarmer(stoi(datas[i]));
        }
        
    }

    
}

void LobbyScreen::setupUIView() {
    Screen::setupUIView();
    View* uiView = new View();
    uiView->setSize(window->getSize().x, window->getSize().y);
    uiView->setCenter(window->getSize().x / 2, window->getSize().y / 2);
    setUIView(uiView);
}

void LobbyScreen::updateScreen(GameEngine* engine) {
    getGameEntitiesByName("EmptySlotText_0")[0]->setVisible(false);

    if(engine->getNetworkManager()->isServer()) {
        engine->getNetworkManager()->handleNewClients();
        
        for(int i = 1; i < engine->getNetworkManager()->getMaxClients()+1; i++) {
            if(engine->getNetworkManager()->hasClient(i)) {
                showFarmer(i);
            } else {
                hideFarmer(i);
            }
        }
    } 

}

void LobbyScreen::handleInput(MappedEvent inputEvent, GameEngine* engine) {
    NetworkManager* networkManager = engine->getNetworkManager();

    switch(inputEvent.eventType) {
        case INPUT_EVENT::ENTER_PRESSED:
            if(networkManager->isServer()) {
                vector<string> datas;
                datas.push_back("GO_TO");
                datas.push_back("MapSelectionScreen");
                networkManager->sendToClients(datas);
                engine->goToScreen("MapSelectionScreen");
            }
            break;
        case INPUT_EVENT::ESCAPE_PRESSED: {
            if(networkManager->isServer()) {
                engine->goToScreen("StartScreen");
                networkManager->stopServer();
            } else {
                engine->goToScreen("ConnectionScreen");
                networkManager->disconnect();
            }
            break;
        }
        default:
            break;
    }
}

void LobbyScreen::handleNetworkServerData(vector<string> datas, GameEngine* engine) {
    Screen::handleNetworkServerData(datas, engine);
    if(datas.size() > 0) {
        if(datas[0] == "CONNECTION_SUCCEED") {
            engine->getNetworkManager()->setId(stoi(datas[1]));
            for(int i = 1; i < datas.size(); i++) {
                showFarmer(stoi(datas[i]));
            }
        }
        if(datas[0] == "CLIENT_CONNECTED") {
            showFarmer(stoi(datas[1]));
        }
        if(datas[0] == "CLIENT_DISCONNECTED") {
            hideFarmer(stoi(datas[1]));
        }
    }

}


void LobbyScreen::generateTitleText() {
    GameEntity* titleTextGameEntity = createUITextGameEntity("LobbyTitle", "Player Lobby", 30, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf");
    titleTextGameEntity->setPosX(window->getSize().x/2 - titleTextGameEntity->getUIText()->getText()->getLocalBounds().width/2);
    titleTextGameEntity->setPosY(30);
    gameEntities.push_back(titleTextGameEntity);
}

void LobbyScreen::generateExitText() {
    GameEntity* exitTextGameEntity = createUITextGameEntity("ExitText", "ESC to disconnect", 15, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf");
    exitTextGameEntity->setPosX(10);
    exitTextGameEntity->setPosY(window->getSize().y - 45);
    gameEntities.push_back(exitTextGameEntity);
}

void LobbyScreen::generateStartText() {
    GameEntity* startTextGameEntity = createUITextGameEntity("StartText", "ENTER to continue", 15, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf");
    startTextGameEntity->setPosX(window->getSize().x - startTextGameEntity->getUIText()->getText()->getLocalBounds().width - 10);
    startTextGameEntity->setPosY(window->getSize().y - 45);
    gameEntities.push_back(startTextGameEntity);
}

void LobbyScreen::generateEmptySlotText(int slotCounts) {
    for(int i = 0; i < slotCounts; i++) {
        GameEntity* emptySlotTextGameEntity = createUITextGameEntity("EmptySlotText_"+to_string(i), "EMPTY SLOT", 15, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf");
        emptySlotTextGameEntity->setPosX(slotPositions[i].x - emptySlotTextGameEntity->getUIText()->getText()->getLocalBounds().width/2);
        emptySlotTextGameEntity->setPosY(slotPositions[i].y);
        gameEntities.push_back(emptySlotTextGameEntity);
    }
}

void LobbyScreen::generateFarmersSprites(int slotCounts) {
    float scale = 4.0f;

    for(int i = 0; i < slotCounts; i++) {
        string farmerSpriteSheetPath = getAssetDirectory() +"Images/Farmers/FarmerSpriteSheet_"+to_string(i)+".png";
        DynamicSprite* farmerSprite = new DynamicSprite(farmerSpriteSheetPath, 28, 47, 1, 0);
        farmerSprite->getSprite()->setScale(scale, scale);

        string gameEntityName = "MainFarmerSprite";

        if(i > 0) {
            gameEntityName = "FarmerSprite_"+to_string(i);
        }
        GameEntity* farmerSpriteGE = new GameEntity(gameEntityName);
        farmerSpriteGE->setRenderMode(RENDER_MODE::UIVIEW);
        farmerSpriteGE->setSprite(farmerSprite);
        farmerSpriteGE->load();
        farmerSpriteGE->setPosX(slotPositions[i].x - (farmerSprite->getSizeX()*scale) / 2);
        farmerSpriteGE->setPosY(slotPositions[i].y - (farmerSprite->getSizeY()*scale) / 2);
        gameEntities.push_back(farmerSpriteGE);
    }   
}

void LobbyScreen::showFarmer(int number) {
    getGameEntitiesByName("FarmerSprite_"+to_string(number))[0]->setVisible(true);
    getGameEntitiesByName("EmptySlotText_"+to_string(number))[0]->setVisible(false);
}

void LobbyScreen::hideFarmer(int number) {
    getGameEntitiesByName("FarmerSprite_"+to_string(number))[0]->setVisible(false);
    getGameEntitiesByName("EmptySlotText_"+to_string(number))[0]->setVisible(true);
}