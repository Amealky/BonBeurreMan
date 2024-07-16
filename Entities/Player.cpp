//
//  Player.cpp
//  BombermanClient
//
//  Created by Amealky on 19/05/2018.
//  Copyright © 2018 Amealky. All rights reserved.
//

#include "Player.hpp"


Player::Player(string name, string spriteSheetPath, int numero, int pv, Bomb* bomb, int bombsCapacityMax, int bombsRefreshDelay) : GameEntity(name) {
    this->numero = numero;
    this->pv = pv;

     
    this->bomb = bomb;
    this->bombsCapacityMax = bombsCapacityMax;
    this->bombsCapacity = this->bombsCapacityMax;
    this->bombsRefreshDelay = bombsRefreshDelay;
    this->bombsRefreshCurrentTime = 0;
    this->bombsRefreshRunning = false;

    DynamicSprite* sprite = new DynamicSprite(spriteSheetPath, 28, 47, 3, 5);
    this->setSprite(sprite);
}

Player::~Player() {}

void Player::ready() {
    sprite->addAnimation("WalkDown", 0);
    sprite->addAnimation("WalkLeft", 4);
    sprite->addAnimation("WalkRight", 8);
    sprite->addAnimation("WalkUp", 12);
    sprite->addAnimation("Dead", 16);

    MoveBody* body = new MoveBody(32, 8, 32);

    Collider* collider = new Collider(new Rect<int>(0, sprite->getSizeY(), sprite->getSizeX(), -10),
                                                0, sprite->getSizeY());

    collider->addPhysicsMask("Blocker");
    collider->addPhysicsMask("Bomb");
    collider->addTriggerMask("Explosion");
    collider->addTriggerMask("Bonus");

    AudioSFX* hurtSound = new AudioSFX(getAssetDirectory() +"Audio/farmer-hurt.mp3", "HurtSound");
    hurtSound->load();
    addAudioSfx(hurtSound);

    AudioSFX* drinkSound = new AudioSFX(getAssetDirectory() +"Audio/drink.mp3", "DrinkSound");
    drinkSound->load();
    addAudioSfx(drinkSound);

    setLayer(3);
    setCollider(collider);
    setBody(body);
}

void Player::update() {
    GameEntity::update();
    if(bombsCapacity < bombsCapacityMax) {
        bombsRefreshCurrentTime += 1;
        if(bombsRefreshCurrentTime >= bombsRefreshDelay) {
            bombsCapacity++;
            bombsRefreshCurrentTime = 0;
        }
    }
}

void Player::onCollisionHappening(GameEntity* other) {
    if(dynamic_cast<ExplosionPart*>(other)) {
        if(networkManager->isServer()) {
            notifyDeadToClients();
            setDeadState();
        } 
    }
    if(dynamic_cast<Bonus*>(other)) {
        Bonus* bonus = dynamic_cast<Bonus*>(other);
        if(!bonus->isUsed()) {
            AudioSFX* drinkSound = getAudioSfxByName("DrinkSound");
            if(drinkSound != NULL) {
                drinkSound->play();
            }
            getBomb()->increaseExplosionDistance(bonus->getDistanceBonus());
            bonus->setUsed(true);
        }
        
    }
}

void Player::onAnimationEnded(string animationName) {
    GameEntity::onAnimationEnded(animationName);
    if(animationName == "Dead") {
        setVisible(false);
    }
}

Bomb* Player::launchBomb() {
    if(!isDead() && canLaunchBomb()) {
        Bomb* bombToLaunch = bomb->copy();
        if(bombToLaunch) {
            bombToLaunch->setPosX(posX);
            bombToLaunch->setPosY(getFeetPosY());
            bombToLaunch->activate();
            this->bombsCapacity--;
            if(networkManager->isServer()) {
                notifyBombLaunchedToClients();
            }
            return bombToLaunch;
        }
    }
    return NULL;
}

void Player::applyMovement() {
    GameEntity::applyMovement();
    if(networkManager->isServer()) {
        notifyMovementToClients();
    }
}

void Player::moveHorizontally(int direction) {
    if(!isDead()) {
        getBody()->setDirectionHorizontal(direction);
        setMoveAnimation(direction, 0);
    }
}

void Player::moveVertically(int direction) {
    if(!isDead()) {
        getBody()->setDirectionVertical(direction);
        setMoveAnimation(0, direction);
    }
}

void Player::setMoveAnimation(int horizontal, int vertical) {
    if(horizontal != 0) {
        if(horizontal > 0) {
            getSprite()->setCurrentAnimation("WalkRight");
        } else {
            getSprite()->setCurrentAnimation("WalkLeft");
        }
    }
    if(vertical != 0) {
        if(vertical > 0) {
            getSprite()->setCurrentAnimation("WalkDown");
        } else {
            getSprite()->setCurrentAnimation("WalkUp");
        }   
    }
}

void Player::setDeadState() {
    if(!isDead()) {
        pv = 0;
        this->getSprite()->setCurrentAnimation("Dead");
        AudioSFX* hurtSound = this->getAudioSfxByName("HurtSound");
        if(hurtSound != NULL) {
            hurtSound->play();
        }


    }
}

bool Player::isDead() {
    return pv <= 0;
}

void Player::askServerForMove(int horizontal, int vertical) {
    vector<string> datas;
    datas.push_back("MOVE");
    datas.push_back(to_string(horizontal));
    datas.push_back(to_string(vertical));
    networkManager->sendToServer(datas);
    setMoveAnimation(horizontal, vertical);

}

void Player::notifyMovementToClients() {
    vector<string> datas;
    datas.push_back("MOVE");
    datas.push_back(to_string(numero));
    datas.push_back(to_string(body->getPosX()));
    datas.push_back(to_string(body->getPosY()));
    datas.push_back(getSprite()->getCurrentAnimationName());
    networkManager->sendToClients(datas);
}

void Player::askServerForPuttingBomb() {
    vector<string> datas;
    datas.push_back("LAUNCH_BOMB");
    networkManager->sendToServer(datas);
}

void Player::notifyBombLaunchedToClients() {
    vector<string> datas;
    datas.push_back("LAUNCH_BOMB");
    datas.push_back(to_string(numero));
    networkManager->sendToClients(datas);
}

void Player::notifyDeadToClients() {
    vector<string> datas;
    datas.push_back("DEAD");
    datas.push_back(to_string(numero));
    networkManager->sendToClients(datas);
}

int Player::getNumero() { 
    return this->numero;
}

int Player::getPv() { 
    return this->pv;
}

Bomb* Player::getBomb() {
    return this->bomb;
}

int Player::getBombsCapacity() {
    return this->bombsCapacity;
}

int Player::getBombsRefreshDelay() {
    return this->bombsRefreshDelay;
}

bool Player::canLaunchBomb() {
    if(bombsCapacity > 0) {
        return true;
    }
    return false;
}

int Player::getFeetPosY() {
    return this->posY + this->getSprite()->getSizeY();
}

void Player::setNumero(int numero) { 
    this->numero = numero;
}

void Player::setPv(int pv) { 
    this->pv = pv;
}
