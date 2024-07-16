#include "ExplosionPart.hpp"


ExplosionPart::ExplosionPart(string name, string spriteSheetPath, EXPLOSION_SIDE side) : GameEntity(name) {
    this->side = side;

    DynamicSprite* sprite = new DynamicSprite(spriteSheetPath, 32, 32, 4, 5);
    this->setSprite(sprite);
    setLayer(2);
    sprite->addAnimation("IDLE", (int)side);
    sprite->setCurrentAnimation("IDLE");
}

ExplosionPart::~ExplosionPart() {}

void ExplosionPart::ready() {
    Collider* collider = new Collider(new Rect<int>(getPosX(), getPosY(), 32, 32), 0, 0); 
    collider->addTriggerLayer("Explosion");            
    collider->addTriggerMask("Destructible");
    setCollider(collider);
}

EXPLOSION_SIDE ExplosionPart::getExplosionSide() {
    return this->side;
}

void ExplosionPart::setExplosionSide(EXPLOSION_SIDE side) {
    this->side = side;
}