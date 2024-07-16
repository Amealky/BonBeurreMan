#include "StartScreen.hpp"


StartScreen::StartScreen(string name, RenderWindow* window) : Screen(name, window) {
    itemSelected = 0;
}

StartScreen::~StartScreen() {
    Screen::~Screen();
}

void StartScreen::launchScreen(GameEngine* engine, vector<string> datas) {
    Screen::launchScreen(engine, datas);

    engine->changeMusic(getAssetDirectory() +"Audio/menu-music.mp3");

    menuItems = {"Start Server", "Join Server"};
    generateBackground();
    generateMenuItemsText();

}

void StartScreen::setupUIView() {
    Screen::setupUIView();

    View* uiView = new View();
    uiView->setSize(window->getSize().x, window->getSize().y);
    uiView->setCenter(window->getSize().x / 2, window->getSize().y / 2);
    this->setUIView(uiView);
}


void StartScreen::updateScreen(GameEngine* engine) {
    vector<GameEntity*> menuItemsGameObjects = getGameEntitiesByName("MenuItem");
    for(int i = 0; i < menuItemsGameObjects.size(); i++) {
        if(i == itemSelected) {
            menuItemsGameObjects[i]->getUIText()->setColor(Color::Yellow);
            continue;
        }
         menuItemsGameObjects[i]->getUIText()->setColor(Color::White);
    }
}

void StartScreen::handleInput(MappedEvent inputEvent, GameEngine* engine) {
    switch (inputEvent.eventType)
    {
        case INPUT_EVENT::UP_PRESSED:
            if(itemSelected > 0) {
                itemSelected--;
            }
            break;
        case INPUT_EVENT::DOWN_PRESSED:
            if(itemSelected < menuItems.size()-1) {
                itemSelected++;
            }
            break;
        case INPUT_EVENT::ENTER_PRESSED:
            if(itemSelected == 0) {
                engine->getNetworkManager()->startServer();
                engine->goToScreen("LobbyScreen");
            } else {
                engine->goToScreen("ConnectionScreen");
            }
            break;
    }

}

void StartScreen::generateBackground() {
    DynamicSprite* background = new DynamicSprite(getAssetDirectory() +"Images/bkgStart.png", window->getSize().x, window->getSize().y, 1, 0);
    GameEntity* backgroundGameEntity = new GameEntity("Background");
    backgroundGameEntity->setSprite(background);
    backgroundGameEntity->setRenderMode(RENDER_MODE::UIVIEW);
    backgroundGameEntity->load();
    gameEntities.push_back(backgroundGameEntity);

}

void StartScreen::generateMenuItemsText() {
    for(int i = 0; i < this->menuItems.size(); i++) {
        GameEntity* itemTextGameEntity = createUITextGameEntity("MenuItem", this->menuItems[i], 30, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf"); 
        itemTextGameEntity->setPosX(window->getSize().x/3);
        itemTextGameEntity->setPosY(window->getSize().y/(this->menuItems.size() + 1) * (i+1));
        gameEntities.push_back(itemTextGameEntity);
    }
}