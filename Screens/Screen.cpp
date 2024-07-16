#include "Screen.hpp"

Screen::Screen(string name, RenderWindow* window) {
    this->name = name;
    this->window = window;
    this->uiView = NULL;
    this->gameView = NULL;
}

Screen::~Screen() {
    delete uiView;
    delete gameView;
    for(GameEntity* gameEntity : gameEntities) {
        delete gameEntity;
    }
    gameEntities.clear();
}

void Screen::launchScreen(GameEngine* engine, vector<string> datas) {
    this->setupUIView();
    this->setupGameView();
}

void Screen::setupUIView() {
    if(uiView != NULL) {
        delete uiView;
    }
}

void Screen::setupGameView() {
    if(gameView != NULL) {
        delete gameView;
    }
}

void Screen::updateScreen(GameEngine* engine) {
    for(GameEntity* gameEntity : gameEntities) {
        gameEntity->update();
    }
}

void Screen::exitScreen(GameEngine* engine) {
    for(GameEntity* gameEntity : gameEntities) {
        delete gameEntity;
    }
    gameEntities.clear();
}

string Screen::getName() {
    return this->name;
}

View* Screen::getUIView() {
    return this->uiView;
}

View* Screen::getGameView() {
    return this->gameView;
}


vector<GameEntity*> Screen::getGameEntities() {
    return this->gameEntities;
}

vector<GameEntity*> Screen::getGameEntitiesByName(string name) {
    vector<GameEntity*> matchingGameEntities;
    for(GameEntity* gameEntity : this->gameEntities) {
        if(gameEntity->getName() == name) {
            matchingGameEntities.push_back(gameEntity);
        }
    }
    return matchingGameEntities;
}

void Screen::setName(string name) {
    this->name = name;
}

void Screen::setUIView(View* uiView) {
    this->uiView = uiView;
}

void Screen::setGameView(View* gameView) {
    this->gameView = gameView;
}


void Screen::setGameEntities(vector<GameEntity*> gameEntities) {
    this->gameEntities = gameEntities;
}

void Screen::removeGameEntity(GameEntity* gameEntity) {
    auto it = std::remove(this->gameEntities.begin(), this->gameEntities.end(), gameEntity);
    this->gameEntities.erase(it, this->gameEntities.end());
}

void Screen::handleNetworkServerData(vector<string> datas, GameEngine* engine) {
    if(!datas.empty()) {
        if(datas[0] == "DISCONNECTED") {
            engine->goToScreen("ConnectionScreen");
        }
        if(datas[0] == "GO_TO") {
            vector<string> additionalGotoData;
            if(datas.size() > 2) {
                for(int i = 2; i < datas.size(); i++) {
                     additionalGotoData.push_back(datas[i]);
                }
            }
            engine->goToScreen(datas[1], additionalGotoData);
        }
    }
}

GameEntity* Screen::createUITextGameEntity(string gameEntityName, string textValue, int characterSize, Color color,  string fontPath) {
    UIText* uiText = new UIText(textValue, characterSize, color, fontPath);
    GameEntity* gameEntity = new GameEntity(gameEntityName);
    gameEntity->setRenderMode(RENDER_MODE::UIVIEW);
    gameEntity->setUIText(uiText);
    gameEntity->load();
    return gameEntity;
}
