#include "MoveBody.hpp"

MoveBody::MoveBody() {
    this->posX = 0;
    this->posY = 0;
    this->speed = 0;
    this->directionHorizontal = 0;
    this->directionVertical = 0;
}

MoveBody::MoveBody(int posX, int posY, int speed) {
    this->posX = posX;
    this->posY = posY;
    this->speed = speed;
    this->directionHorizontal = 0;
    this->directionVertical = 0;
}

MoveBody::~MoveBody() {}

void MoveBody::move() {
    float horizontalMove = speed * directionHorizontal;
    float verticalMove = speed * directionVertical;
    posX += horizontalMove;
    posY += verticalMove;

}

int MoveBody::getPosX() {
    return this->posX;
}

int MoveBody::getPosY() {
    return this->posY;
}

int MoveBody::getSpeed() {
    return this->speed;
}

int MoveBody::getDirectionHorizontal() {
    return this->directionHorizontal;
}

int MoveBody::getDirectionVertical() {
    return this->directionVertical;
}


void MoveBody::setPosX(int posX) {
    this->posX = posX;
}

void MoveBody::setPosY(int posY) {
    this->posY = posY;
}

void MoveBody::setSpeed(int speed) {
    this->speed = speed;
} 

void MoveBody::setDirectionHorizontal(int directionHorizontal) {
    this->directionHorizontal = directionHorizontal;
} 

void MoveBody::setDirectionVertical(int directionVertical) {
    this->directionVertical = directionVertical;
}
