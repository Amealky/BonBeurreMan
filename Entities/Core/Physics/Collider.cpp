#include "Collider.hpp"

Collider::Collider() {
    this->rect = NULL;
    this->relativePosX = 0;
    this->relativePosY = 0;
}

Collider::Collider(Rect<int>* rect, int relativePosX, int relativePosY) {
    this->rect = rect;
    this->relativePosX = relativePosX;
    this->relativePosY = relativePosY;
}

Collider::~Collider() {
    delete rect;
}

void Collider::relativeMove(int parentPosX, int parentPosY) {
    this->rect->left = relativePosX + parentPosX;
    this->rect->top = relativePosY + parentPosY;
}

Rect<int>* Collider::getColliderRect() {
    return this->rect;
}

int Collider::getRelativePosX() {
    return this->relativePosX;
}

int Collider::getRelativePosY() {
    return this->relativePosY;
}

vector<string> Collider::getPhysicsLayer() {
    return this->physicsLayers;
}

vector<string> Collider::getTriggerLayer() {
    return this->triggerLayers;
}

vector<string> Collider::getPhysicsMasks() {
    return this->physicsMasks;
}

vector<string> Collider::getTriggerMasks() {
    return this->triggerMasks;
}


void Collider::setColliderRect(Rect<int>* rect) {
    this->rect = rect;
}

void Collider::setRelativePosX(int relativePosX) {
    this->relativePosX = relativePosX;
}

void Collider::setRelativePosY(int relativePosY) {
    this->relativePosY = relativePosY;
}

void Collider::addPhysicsLayer(string layer) {
    this->physicsLayers.push_back(layer);
}

void Collider::addTriggerLayer(string layer) {
    this->triggerLayers.push_back(layer);
}

void Collider::addPhysicsMask(string mask) {
    this->physicsMasks.push_back(mask);
}

void Collider::addTriggerMask(string mask) {
    this->triggerMasks.push_back(mask);
}

void Collider::removePhysicsLayer(string layer) {
    auto it = std::remove(this->physicsLayers.begin(), this->physicsLayers.end(), layer);
    this->physicsLayers.erase(it, this->physicsLayers.end());
}

void Collider::removeTriggerLayer(string layer) {
    auto it = std::remove(this->triggerLayers.begin(), this->triggerLayers.end(), layer);
    this->triggerLayers.erase(it, this->triggerLayers.end());
}

void Collider::removePhysicsMask(string mask) {
    auto it = std::remove(this->physicsMasks.begin(), this->physicsMasks.end(), mask);
    this->physicsMasks.erase(it, this->physicsMasks.end());
}

void Collider::removeTriggerMask(string mask) {
    auto it = std::remove(this->triggerMasks.begin(), this->triggerMasks.end(), mask);
    this->triggerMasks.erase(it, this->triggerMasks.end());
}