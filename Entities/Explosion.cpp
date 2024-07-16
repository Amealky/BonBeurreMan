#include "Explosion.hpp"

Explosion::Explosion(string name, string spriteSheetPath, int distance, int explosionDuration) : GameEntity(name) {
    this->distance = distance;
    this->explosionDuration = explosionDuration;
    this->explosionCurrentTime = explosionDuration;

    DynamicSprite* sprite = new DynamicSprite(spriteSheetPath);
    this->setSprite(sprite);
}

Explosion::~Explosion() {}

void Explosion::ready() {

    AudioSFX* explosionSound = new AudioSFX(getAssetDirectory() +"Audio/Proutch.ogg", "ExplosionSound");
    explosionSound->load();
    addAudioSfx(explosionSound);
    if(explosionSound != NULL) {
        explosionSound->play();
    }
}

void Explosion::update() {
    explosionCurrentTime -= 1;
    
}

void Explosion::generateExplosionLines(Map* map) {
    generateExplosionCenter();
    generateExplosionLine(EXPLOSION_SIDE::END_UP, 0, -1, map);
    generateExplosionLine(EXPLOSION_SIDE::END_LEFT, -1, 0, map);
    generateExplosionLine(EXPLOSION_SIDE::END_DOWN, 0, 1, map);
    generateExplosionLine(EXPLOSION_SIDE::END_RIGHT, 1, 0, map);
}


Explosion* Explosion::copy() {
    Explosion* newExplosion = new Explosion(this->getName(), this->getSprite()->getSpriteSheetPath(), this->distance, this->explosionDuration);
    newExplosion->load();
    return newExplosion;
}

int Explosion::getDistance() {
    return this->distance;
}

int Explosion::getExplosionDuration() {
    return this->explosionDuration;
}

int Explosion::getCurrentTime() {
    return this->explosionCurrentTime;
}

void Explosion::setDistance(int distance) {
    this->distance = distance;
}

void Explosion::setExplosionDuration(int duration) {
    this->explosionDuration = duration;
}


void Explosion::generateExplosionLine(EXPLOSION_SIDE endSide, int directionX, int directionY, Map* map) {

    for(int i = 1; i <= this->distance; i++) {

        if(i == this->distance) {
            generateExplosionPart(endSide, i, directionX, directionY, map);
            return;
        }

        if(directionY != 0) {
            if(!generateExplosionPart(EXPLOSION_SIDE::VERTICAL, i, directionX, directionY, map)) {
                return;
            }
        }
        if(directionX != 0) {
            if(!generateExplosionPart(EXPLOSION_SIDE::HORIZONTAL, i, directionX, directionY, map)) {
                return;
            }
        }
    }
}

void Explosion::generateExplosionCenter() {
    string spriteSheetPath = this->getSprite()->getSpriteSheetPath();
    ExplosionPart* explosionPart = new ExplosionPart("ExplosionCenter", spriteSheetPath, EXPLOSION_SIDE::CENTER);

    int explosionPartSizeX = explosionPart->getSprite()->getSizeX();
    int explosionPartSizeY = explosionPart->getSprite()->getSizeY();
    int explosionPartPosX = this->getPosX();
    int explosionPartPosY = this->getPosY();

    explosionPart->setPosX(explosionPartPosX);
    explosionPart->setPosY(explosionPartPosY);
    explosionPart->load();

    this->addChild(explosionPart);
}

bool Explosion::generateExplosionPart(EXPLOSION_SIDE side, int partNumber, int directionX, int directionY, Map* map) {
    string spriteSheetPath = this->getSprite()->getSpriteSheetPath();
    ExplosionPart* explosionPart = new ExplosionPart("ExplosionPart_side"+to_string((int)side)+"_"+to_string(partNumber), spriteSheetPath, side);

    int explosionPartSizeX = explosionPart->getSprite()->getSizeX();
    int explosionPartSizeY = explosionPart->getSprite()->getSizeY();
    int explosionPartPosX = this->getPosX() + (partNumber * explosionPartSizeX * directionX);
    int explosionPartPosY = this->getPosY() + (partNumber * explosionPartSizeY * directionY);
    
    explosionPart->setPosX(explosionPartPosX);
    explosionPart->setPosY(explosionPartPosY);

    explosionPart->load();

    //Check if there is a tile on the way
    Tile* tileAtPos = map->getTileAtPos(explosionPartPosX, explosionPartPosY, 1);
    
    bool noBlockerOnTheWay = true;

    if(tileAtPos != NULL) {
        if(map->isTileIsBlocker(tileAtPos)) {
            if(tileAtPos->getId() == (int)TILES::DESTRUCTIBLE_WALL) {
                this->addChild(explosionPart);
            } else {
                delete explosionPart;
            }
            return false;
        }
    }

    
    this->addChild(explosionPart);
    return true;
}
