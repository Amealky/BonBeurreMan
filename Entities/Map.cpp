#include "Map.hpp"


Map::Map(string name, string mapPath, string tilesetPath) : Tilemap(name, mapPath, tilesetPath) {}

void Map::ready() {
    Tilemap::ready();
    for(GameEntity* child : childs) {
        if(Tile* tile = dynamic_cast<Tile*>(child)) {
            switch(static_cast<TILES>(tile->getId())) {
                case TILES::BOTTOM_WALL:
                case TILES::BOTTOM_LEFT_CORNER:
                case TILES::BOTTOM_RIGHT_CORNER:
                case TILES::TOP_WALL:
                case TILES::TOP_LEFT_CORNER:
                case TILES::TOP_RIGHT_CORNER:
                case TILES::LEFT_WALL:
                case TILES::RIGHT_WALL:
                case TILES::DESTRUCTIBLE_WALL:
                case TILES::PILLAR:
                    Collider* tileCollider = new Collider(new Rect<int>(tile->getPosX(), tile->getPosY(), 32, 32), 0, 0);
                    if (static_cast<TILES>(tile->getId()) == TILES::DESTRUCTIBLE_WALL) {
                        tileCollider->addTriggerLayer("Destructible");
                    }
                    tileCollider->addPhysicsLayer("Blocker");
                    tile->setCollider(tileCollider);
                    

            }
        }
    }

    AudioSFX* explodedSound = new AudioSFX(getAssetDirectory() +"Audio/hay-explode.mp3", "ExplodedSound");
    explodedSound->load();
    addAudioSfx(explodedSound);
    
}

Map::~Map() {}

void Map::update() {
    for(GameEntity* child : childs) {
        if(Bonus* bonus = dynamic_cast<Bonus*>(child)) {
            if(bonus->isUsed()) {
                removeChild(bonus);
                delete bonus;
            }
        }
    }
}

void Map::onCollisionHappeningOnTile(GameEntity* other) {
    Tile* tileColliding = getTileAtPos(other->getPosX(), other->getPosY(), 1);
    if(tileColliding != NULL) {
        if(static_cast<TILES>(tileColliding->getId()) == TILES::DESTRUCTIBLE_WALL && dynamic_cast<ExplosionPart*>(other)) {
            if(networkManager->isServer()) {
                notifyDestructionToClients(tileColliding->getPosX(), tileColliding->getPosY());
                destroyTile(tileColliding);
            }
        }
    }

}

void Map::centerGameEntity(GameEntity* gameEntity) {
    gameEntity->setPosX(int(gameEntity->getPosX() / getTileSize()) * getTileSize());
    gameEntity->setPosY(int(gameEntity->getPosY() / getTileSize()) * getTileSize());
}


bool Map::isTileIsBlocker(Tile* tile) {
    if(tile->getCollider() != NULL) {
        if(contains(tile->getCollider()->getPhysicsLayer(), "Blocker")) {
            return true;
        }
    }

    return false;
}

void Map::destroyTile(Tile* tileToDestroy) {
    AudioSFX* explodedSound = getAudioSfxByName("ExplodedSound");
    if(explodedSound != NULL) {
        explodedSound->play();
    }
    if(networkManager->isServer()) {
        generateBonus(randomChance(3), tileToDestroy->getPosX(), tileToDestroy->getPosY());
    }
    removeChild(tileToDestroy);
    delete tileToDestroy;
}

void Map::generateBonus(bool shouldGenerate, int posX, int posY) {
    if(shouldGenerate) {
        if(networkManager->isServer()) {
            notifyBonusAppearToClients(posX, posY);
        }
        Bonus* bonus = new Bonus("MilkBonus", getAssetDirectory() +"Images/Milk/Milk_spritesheet.png", 1);
        bonus->setPosX(posX);
        bonus->setPosY(posY);
        bonus->load();
        addChild(bonus);
    }
}

void Map::notifyDestructionToClients(int tilePosX, int tilePosY) {
    vector<string> datas;
    datas.push_back("TILE_DESTROYED");
    datas.push_back(to_string(tilePosX));
    datas.push_back(to_string(tilePosY));
    networkManager->sendToClients(datas);
}

void Map::notifyBonusAppearToClients(int bonusPosX, int bonusPosY) {
    vector<string> datas;
    datas.push_back("BONUS_APPEAR");
    datas.push_back(to_string(bonusPosX));
    datas.push_back(to_string(bonusPosY));
    networkManager->sendToClients(datas);
}
