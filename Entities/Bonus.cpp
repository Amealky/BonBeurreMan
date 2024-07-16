#include "Bonus.hpp"

Bonus::Bonus(string name, string spriteSheetPath, int distanceBonus) : GameEntity(name) {
    this->distanceBonus = distanceBonus;
    this->used = false;

    DynamicSprite* sprite = new DynamicSprite(spriteSheetPath, 32, 32, 4, 10);
    sprite->addAnimation("IDLE", 0);
    sprite->setCurrentAnimation("IDLE");
    sprite->setLooping(true);
    this->setSprite(sprite);
}

Bonus::~Bonus() {}

void Bonus::ready() {
    Collider* collider = new Collider(new Rect<int>(getPosX(), getPosY(), 32, 32), 0, 0);
    collider->addTriggerLayer("Bonus");
    setCollider(collider);
    setLayer(1);
}

int Bonus::getDistanceBonus() {
    return this->distanceBonus;
}

bool Bonus::isUsed() {
    return this->used;
}

void Bonus::setDistanceBonus(int distanceBonus) {
    this->distanceBonus = distanceBonus;
}

void Bonus::setUsed(bool used) {
    this->used = used;
}