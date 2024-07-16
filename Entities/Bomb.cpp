#include "Bomb.hpp"

Bomb::Bomb(string name) : GameEntity(name) {
    this->explosion = NULL;
    this->activated = 0;
    this->exploded = false;
    this->delayBeforeExplosion = 1;
    this->currentTimeBeforeExplosion = delayBeforeExplosion;
}

Bomb::Bomb(string name, string spriteSheetPath, Explosion* explosion, float delayBeforeExplosion) : GameEntity(name) {
    this->explosion = explosion;
    this->activated = 0;
    this->exploded = false;
    this->delayBeforeExplosion = delayBeforeExplosion;
    this->currentTimeBeforeExplosion = delayBeforeExplosion;

    DynamicSprite* sprite = new DynamicSprite(spriteSheetPath, 32, 32, 2, 25);
    sprite->addAnimation("IDLE", 0);
    sprite->setCurrentAnimation("IDLE");
    sprite->setLooping(true);
    this->setSprite(sprite);

}

Bomb::~Bomb() {}

void Bomb::ready() {
    Collider* collider = new Collider(new Rect<int>(0, 0, 32, 32), 0, 0);
    collider->addPhysicsLayer("Bomb");
    setCollider(collider);
    setLayer(2);
}

void Bomb::update() {
    GameEntity::update();

    if(activated) {
        currentTimeBeforeExplosion -= 1;
        if(currentTimeBeforeExplosion <= 0) {
            explode();
        }
    }

}

Explosion* Bomb::generateExplosion(Map* map) {
    Explosion* explosion = this->explosion->copy();

    if(explosion) {
        explosion->setPosX(this->getPosX());
        explosion->setPosY(this->getPosY());
        explosion->generateExplosionLines(map);
        return explosion;
    }

    return NULL;
}

void Bomb::increaseExplosionDistance(int distanceBonus) {
    int newDistance = getExplosion()->getDistance() + distanceBonus;
    getExplosion()->setDistance(newDistance);
}

Bomb* Bomb::copy() {
    Bomb* newBomb = new Bomb(this->getName(), this->getSprite()->getSpriteSheetPath(), this->explosion, this->delayBeforeExplosion);
    newBomb->load();
    return newBomb;
}

Explosion* Bomb::getExplosion() {
    this->explosion->setPosX(this->getPosX());
    this->explosion->setPosY(this->getPosY());
    return this->explosion;
}

bool Bomb::isActivated(){
    return this->activated;
}

bool Bomb::isExploded() {
    return this->exploded;
}

int Bomb::getDelayBeforeExplosion(){
    return this->delayBeforeExplosion;
}
int Bomb::getCurrentTimeBeforeExplosion() {
    return this->currentTimeBeforeExplosion;
}


void Bomb::activate() {
    this->activated = true;
}

void Bomb::explode() {
    this->exploded = true;
}

void Bomb::setExplosion(Explosion* explosion) {
    this->explosion = explosion;
}


void Bomb::setDelayBeforeExplosion(int delay){
    this->delayBeforeExplosion = delay;
}
