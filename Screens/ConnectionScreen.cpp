#include "ConnectionScreen.hpp"

ConnectionScreen::ConnectionScreen(string name, RenderWindow* window) : Screen(name, window) {}

ConnectionScreen::~ConnectionScreen() {
    Screen::~Screen();
}

void ConnectionScreen::launchScreen(GameEngine* engine, vector<string> datas) {
    Screen::launchScreen(engine, datas);

    generateTitleText();
    generateIPEditText();
    generatePortText(to_string(engine->getNetworkManager()->getPort()));
    generateExitText();
    generateConnectText();
    generateLoadingStatus();

}

void ConnectionScreen::setupUIView() {
    Screen::setupUIView();

    View* uiView = new View();
    uiView->setSize(window->getSize().x, window->getSize().y);
    uiView->setCenter(window->getSize().x / 2, window->getSize().y / 2);
    this->setUIView(uiView);
}

void ConnectionScreen::handleInput(MappedEvent inputEvent, GameEngine* engine) {
    switch(inputEvent.eventType) {
        case INPUT_EVENT::NUMBER_ENTERED:
            getGameEntitiesByName("IPEditText")[0]->getUIEditText()->addChar(inputEvent.c);
            break;
        case INPUT_EVENT::BACK_SPACE_PRESSED:
            getGameEntitiesByName("IPEditText")[0]->getUIEditText()->removeChar();
            break;
        case INPUT_EVENT::ENTER_PRESSED:
            if(tryConnection(engine->getNetworkManager())) {
                engine->goToScreen("LobbyScreen");
            }
            break;
        case INPUT_EVENT::ESCAPE_PRESSED:
            engine->goToScreen("StartScreen");
            break;
        default:
            break;
    }
    
}

void ConnectionScreen::generateTitleText() {
    GameEntity* titleTextGameEntity = createUITextGameEntity("ConnectionTitle", "Server IP to connect", 30, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf"); 
    titleTextGameEntity->setPosX(window->getSize().x/2 - titleTextGameEntity->getUIText()->getText()->getLocalBounds().width/2);
    titleTextGameEntity->setPosY(30);
    gameEntities.push_back(titleTextGameEntity);
}

void ConnectionScreen::generateIPEditText() {
    UIEditText* ipEditText = new UIEditText(250, 50, 15, 20, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf");
    ipEditText->setMarginX(10);
    GameEntity* ipEditTextGE = new GameEntity("IPEditText");
    ipEditTextGE->setRenderMode(RENDER_MODE::UIVIEW);
    ipEditTextGE->setUIEditText(ipEditText);
    ipEditTextGE->load();
    
    ipEditTextGE->setPosX(window->getSize().x/2 - ipEditText->getBackground()->getLocalBounds().width/2);
    ipEditTextGE->setPosY(window->getSize().y/2);
    gameEntities.push_back(ipEditTextGE);
}

void ConnectionScreen::generatePortText(string portValue) {
    GameEntity* portTextGameEntity = createUITextGameEntity("PortText", "Port : " + portValue, 15, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf"); 
    portTextGameEntity->setPosX(window->getSize().x/2 - portTextGameEntity->getUIText()->getText()->getLocalBounds().width/2);
    portTextGameEntity->setPosY(window->getSize().y/2 + 75);
    gameEntities.push_back(portTextGameEntity);
}

void ConnectionScreen::generateExitText() {
    GameEntity* exitTextGameEntity = createUITextGameEntity("ExitText", "ESC to go back", 15, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf"); 
    exitTextGameEntity->setPosX(10);
    exitTextGameEntity->setPosY(window->getSize().y - 45);
    gameEntities.push_back(exitTextGameEntity);
}

void ConnectionScreen::generateConnectText() {
    GameEntity* connectionTextGameEntity = createUITextGameEntity("ConnectionText", "ENTER to connect", 15, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf"); 
    connectionTextGameEntity->setPosX(window->getSize().x - connectionTextGameEntity->getUIText()->getText()->getLocalBounds().width - 10);
    connectionTextGameEntity->setPosY(window->getSize().y - 45);
    gameEntities.push_back(connectionTextGameEntity);
}

void ConnectionScreen::generateLoadingStatus() {
    GameEntity* loadingStatusGameEntity = createUITextGameEntity("LoadingStatus", "Connection Failed", 15, Color::Blue, getAssetDirectory() +"Fonts/pixelFont.otf"); 
    loadingStatusGameEntity->setVisible(false);
    loadingStatusGameEntity->setPosX(window->getSize().x - loadingStatusGameEntity->getUIText()->getText()->getLocalBounds().width - 10);
    loadingStatusGameEntity->setPosY(window->getSize().y - 75);
    gameEntities.push_back(loadingStatusGameEntity);
}

bool ConnectionScreen::tryConnection(NetworkManager* networkManager) {
    GameEntity* loadingStatus = getGameEntitiesByName("LoadingStatus")[0];
    loadingStatus->getUIText()->setTextValue("Connection ...");
    loadingStatus->getUIText()->setColor(Color::Blue);
    loadingStatus->setVisible(true);

    string ip = getGameEntitiesByName("IPEditText")[0]->getUIEditText()->getUIText()->getTextValue();
    if(networkManager->connectServer(ip)) {
        return true;
    } else {
        loadingStatus->getUIText()->setTextValue("Connection Failed");
        loadingStatus->getUIText()->setColor(Color::Red);
        return false;
    }
}