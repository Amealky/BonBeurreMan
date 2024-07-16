#include "Tile.hpp"

Tile::Tile(string name) : GameEntity(name) {
    this->id = 0;
    tileListener = NULL;
}

Tile::Tile(string name, string tilesetPath, int id) : GameEntity(name) {
    DynamicSprite* dynamicSprite = new DynamicSprite(tilesetPath);
    this->setSprite(dynamicSprite);
    this->id = id;
    tileListener = NULL;
}

Tile::~Tile() {}

void Tile::onCollisionHappening(GameEntity* other) {
    this->tileListener->onCollisionHappeningOnTile(other);
}

int Tile::getId() {
    return this->id;
}

void Tile::setTileListener(TileListener* tileListener) {
    this->tileListener = tileListener;
}
