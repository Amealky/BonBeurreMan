#include "Server.hpp"

Server::Server() {}

void Server::setGameEntities(vector<GameEntity*> gameEntities) {
    this->gameEntities = gameEntities;
}

void Server::addGameEntity(GameEntity* gameEntity) {
    this->gameEntities.push_back(gameEntity);
}

void Server::clearEntities() {
    this->gameEntities.clear();
}