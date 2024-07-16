#include "ArenaScreen.hpp"

ArenaScreen::ArenaScreen(string name, RenderWindow* window) : Screen(name, window) {
    gameIsDone = false;
}

ArenaScreen::~ArenaScreen() {
    Screen::~Screen();
}

void ArenaScreen::launchScreen(GameEngine* engine, vector<string> datas) {
    engine->changeMusic(getAssetDirectory() +"Audio/arena-music.mp3");

    NetworkManager* networkManager = engine->getNetworkManager();

    int currentMapIndex = stoi(datas[0]);

    generateMap(currentMapIndex);
    generatePlayers(datas);
    generateWinMessage();
    generateExitText();
  

    Screen::launchScreen(engine, datas);
}

void ArenaScreen::setupUIView() {
  Screen::setupUIView();
  View* uiView = new View();
  uiView->setSize(window->getSize().x, window->getSize().y);
  uiView->setCenter(window->getSize().x / 2, window->getSize().y / 2);
  this->setUIView(uiView);
}

void ArenaScreen::setupGameView() {
  Screen::setupGameView();

  vector<Map*> maps = getGameEntitiesOfType<Map>();
  if(maps.size() > 0) {
    Map* map = maps[0];
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

void ArenaScreen::updateScreen(GameEngine* engine) {
  Screen::updateScreen(engine);


  gameIsDone = checkGameIsDone();

  if(gameIsDone) {
    showWinMessage();
    if(engine->getNetworkManager()->isServer()) {
      showExitText();
    }
  } else {
    hideEndGameUI();
  }


  for(Bomb* bomb : getGameEntitiesOfType<Bomb>()) {
    if(bomb->isExploded()) {
        Explosion* explosion = bomb->generateExplosion(dynamic_cast<Map*>(gameEntities[0]));
        gameEntities.push_back(explosion);
        removeGameEntity(bomb);
        delete bomb;
    }
  }

  for(Explosion* explosion : getGameEntitiesOfType<Explosion>()) {
    if(explosion->getCurrentTime() <= 0) {
        removeGameEntity(explosion);
        delete explosion;
    }
  }


}

void ArenaScreen::handleInput(MappedEvent inputEvent, GameEngine* engine) {
    NetworkManager* networkManager = engine->getNetworkManager();
    int playerId = networkManager->isServer() ? 0 : networkManager->getId();

    switch(inputEvent.eventType) {
      case INPUT_EVENT::ESCAPE_PRESSED: {
        if(gameIsDone && networkManager->isServer()) {
          vector<string> datas;
          datas.push_back("GO_TO");
          datas.push_back("MapSelectionScreen");
          networkManager->sendToClients(datas);
          engine->goToScreen("MapSelectionScreen");
        }
        break;
      }
      case INPUT_EVENT::UP_PRESSED:
        if(networkManager->isServer()) {
          getGameEntitiesOfType<Player>()[playerId]->moveVertically(-1);
        } else {
          getGameEntitiesOfType<Player>()[playerId]->askServerForMove(0, -1);
        }
        break;
      case INPUT_EVENT::DOWN_PRESSED:
        if(networkManager->isServer()) {
          getGameEntitiesOfType<Player>()[playerId]->moveVertically(1);
        }else {
          getGameEntitiesOfType<Player>()[playerId]->askServerForMove(0, 1);
        }
        break;
      case INPUT_EVENT::LEFT_PRESSED:
        if(networkManager->isServer()) {
          getGameEntitiesOfType<Player>()[playerId]->moveHorizontally(-1);
        }else {
          getGameEntitiesOfType<Player>()[playerId]->askServerForMove(-1, 0);
        }
        break;
      case INPUT_EVENT::RIGHT_PRESSED:
        if(networkManager->isServer()) {
          getGameEntitiesOfType<Player>()[playerId]->moveHorizontally(1);
        }else {
          getGameEntitiesOfType<Player>()[playerId]->askServerForMove(1, 0);
        }
        break;
      case INPUT_EVENT::BOMB: {
          if(networkManager->isServer()) {
            putBomb(0);
          } else { 
            getGameEntitiesOfType<Player>()[playerId]->askServerForPuttingBomb();
          }
        }
        break;
      default:
        break;
    }
}

void ArenaScreen::handleNetworkClientsData(unordered_map<string, vector<string>> datas, GameEngine* engine) {
  vector<Player*> players = getGameEntitiesOfType<Player>();
  for (auto& pair : datas) {
      int clientId = stoi(pair.first);
      vector<string> values = pair.second;

      if(values.size() > 0) {
        if(values[0] == "MOVE") {
          int directionHorizontal = stoi(values[1]);
          int directionVertical = stoi(values[2]);
          for(Player* player : players) {
            if(player->getNumero() == clientId) {
              if(directionHorizontal != 0) {
                player->moveHorizontally(directionHorizontal);
              } else {
                player->moveVertically(directionVertical);
              }
            }
          }
        }
        else if(values[0] == "LAUNCH_BOMB") {
          putBomb(clientId);
        }
        else if(values[0] == "DISCONNECTED") {
            for(Player* player : getGameEntitiesOfType<Player>()) {
              if(player->getNumero() == clientId) {
                player->setDeadState();
              } 
            }
        }
      }
  }
}

void ArenaScreen::handleNetworkServerData(vector<string> datas, GameEngine* engine) {
  vector<Player*> players = getGameEntitiesOfType<Player>();
  Map* actualMap = getGameEntitiesOfType<Map>()[0];

  if(datas.size() > 0) {
    if(datas[0] == "MOVE") {
      int playerId = stoi(datas[1]);
      int newPosX = stoi(datas[2]);
      int newPosY = stoi(datas[3]);
      string newAnimToPlay = datas[4];
      for(Player* player : players) {
        if(player->getNumero() == playerId) {
          player->getBody()->setPosX(newPosX);
          player->getBody()->setPosY(newPosY);
          player->getSprite()->setCurrentAnimation(newAnimToPlay);
        }
      }
    } else if(datas[0] == "LAUNCH_BOMB") {
      putBomb(stoi(datas[1]));
    } else if(datas[0] == "TILE_DESTROYED") {
      Tile* tileToDestroy = actualMap->getTileAtPos(stoi(datas[1]), stoi(datas[2]), 1);
      actualMap->destroyTile(tileToDestroy);
    } else if(datas[0] == "BONUS_APPEAR") {
      actualMap->generateBonus(true, stoi(datas[1]), stoi(datas[2]));
    } else if(datas[0] == "DEAD") {
      int playerId = stoi(datas[1]);
      for(Player* player : players) {
        if(player->getNumero() == playerId) {
          player->setDeadState();
        }
      }
    }
  }

  Screen::handleNetworkServerData(datas, engine);
}

void ArenaScreen::exitScreen(GameEngine* engine) {
  Screen::exitScreen(engine);
  engine->changeMusic(getAssetDirectory() +"Audio/menu-music.mp3");
}

void ArenaScreen::generateMap(int mapNumber) {
    vector<string> mapFiles = listFilesFrom(getAssetDirectory() +"Maps/", "tmap");
    Map* map = new Map("ArenaMap", mapFiles[mapNumber], getAssetDirectory() +"Images/Barn/BarnTileset.png");
    map->load();
    gameEntities.push_back(map);
}


Bomb* ArenaScreen::generateBasicBomb() {
  Explosion* basicExplosion = new Explosion("Explosion", getAssetDirectory() +"Images/Butter/ButterExplosionSpriteSheet.png", 1, 25);
  Bomb* basicBomb = new Bomb("Bomb", getAssetDirectory() +"Images/Butter/ButterIdleSpriteSheet.png", basicExplosion, 100);
  basicBomb->load();
  return basicBomb;
}

void ArenaScreen::generatePlayers(vector<string> clientIds) {
    Map* actualMap = getGameEntitiesOfType<Map>()[0];

    Player* mainFarmer = new Player("MainFarmer", getAssetDirectory() +"Images/Farmers/FarmerSpriteSheet_0.png", 0, 1, generateBasicBomb(), 2, 110);
    mainFarmer->load();
    gameEntities.push_back(mainFarmer);

    for(int i = 1; i < clientIds.size(); i++) {
      string clientId = clientIds[i];
      Player* clientFarmer = new Player("ClientFarmer", getAssetDirectory() +"Images/Farmers/FarmerSpriteSheet_"+clientId+".png", stoi(clientId), 1, generateBasicBomb(), 2, 5);
      clientFarmer->load();
      switch(i) {
        case 1:
          clientFarmer->getBody()->setPosX(actualMap->getWidthInPixel()-actualMap->getTileSize()*2);
          break;
        case 2:
          clientFarmer->getBody()->setPosY(actualMap->getHeightinPixel()-actualMap->getTileSize()*3 + 8);
          break;
        case 3:
          clientFarmer->getBody()->setPosX(actualMap->getWidthInPixel()-actualMap->getTileSize()*2);
          clientFarmer->getBody()->setPosY(actualMap->getHeightinPixel()-actualMap->getTileSize()*3+ 8);
          break;
        default:
          break;
      }
      gameEntities.push_back(clientFarmer);   
    }
}

void ArenaScreen::generateWinMessage() {
    GameEntity* winMessageGameEntity = createUITextGameEntity("WinMessage", "Player 1 win !", 30, Color::Green, getAssetDirectory() +"Fonts/pixelFont.otf"); 
    winMessageGameEntity->setPosX(window->getSize().x/2 - winMessageGameEntity->getUIText()->getText()->getLocalBounds().width/2);
    winMessageGameEntity->setPosY(30);
    gameEntities.push_back(winMessageGameEntity);
}

void ArenaScreen::generateExitText() {
    GameEntity* exitTextGameEntity = createUITextGameEntity("ExitText", "ESC to go back", 15, Color::White, getAssetDirectory() +"Fonts/pixelFont.otf"); 
    exitTextGameEntity->setPosX(10);
    exitTextGameEntity->setPosY(window->getSize().y - 45);
    gameEntities.push_back(exitTextGameEntity);
}

bool ArenaScreen::checkGameIsDone() {
  vector<Player*> playersAlive = getGameEntitiesOfType<Player>();
  for(auto it = playersAlive.begin(); it != playersAlive.end(); ) {
    if ((*it)->isDead()) {
        it = playersAlive.erase(it);
    } else {
        ++it;
    }
  }

  if(playersAlive.size() == 1) {
    getGameEntitiesByName("WinMessage")[0]->getUIText()->setTextValue("Player " + to_string(playersAlive[0]->getNumero()+1) + " Win !");
    return true;
  }

  return false;

}

void ArenaScreen::showWinMessage() {
  getGameEntitiesByName("WinMessage")[0]->setVisible(true);
}

void ArenaScreen::showExitText() {
  getGameEntitiesByName("ExitText")[0]->setVisible(true);
}


void ArenaScreen::hideEndGameUI() {
    getGameEntitiesByName("WinMessage")[0]->setVisible(false);
    getGameEntitiesByName("ExitText")[0]->setVisible(false);
}


void ArenaScreen::putBomb(int playerId) {
    Map* map = getGameEntitiesOfType<Map>()[0];
    Bomb* bombLaunched = getGameEntitiesOfType<Player>()[playerId]->launchBomb();
    if(bombLaunched != NULL) {
      map->centerGameEntity(bombLaunched);
      gameEntities.push_back(bombLaunched);
    }
}
