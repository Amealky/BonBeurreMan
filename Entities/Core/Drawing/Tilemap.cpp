#include "Tilemap.hpp"


Tilemap::Tilemap(string name, string mapPath, string tilesetPath) : GameEntity(name) {
    width = 0;
    height = 0;
    tileSize = 0;
    this->mapPath = mapPath;

    DynamicSprite* dynamicSprite = new DynamicSprite(tilesetPath);
    this->setSprite(dynamicSprite);
}

Tilemap::~Tilemap() {}

void Tilemap::ready() {
    vector<vector<string>> mapArray = fileToArray(mapPath);

    int posX = stoi(mapArray[0][1]);
    int posY = stoi(mapArray[0][2]);
    int sizeX = stoi(mapArray[0][3]);
    int sizeY = stoi(mapArray[0][4]);
    int tileSize = stoi(mapArray[0][5]);

    setPosX(posX);
    setPosY(posY);
    this->width = sizeX;
    this->height = sizeY;
    this->tileSize = tileSize;

    int layer = 0;

    //Remove first line of informations
    mapArray.erase(mapArray.begin());
   
    for(int y = 0; y < mapArray.size(); y++) {
        //The current layer is the y pos / by tile height ( for a height of 10 : 0-10 /10 = layer 0 etc )
        layer = y / height;
        for(int x = 0; x < mapArray[y].size(); x++) {
            int tileId = stoi(mapArray[y][x]);
            Tile* tile = new Tile("Tile_x"+to_string(x)+"_y"+to_string(y), getSprite()->getSpriteSheetPath(), tileId);
            tile->setLayer(layer);
            tile->load();

            //Also set the position here
            tile->setPosX(x*tileSize);
            tile->setPosY((y % height) * tileSize);
            tile->getSprite()->setSizeX(tileSize);
            tile->getSprite()->setSizeY(tileSize);
            tile->getSprite()->addAnimation("IDLE", tileId);
            tile->getSprite()->setCurrentAnimation("IDLE");
            tile->setTileListener(this);
            childs.push_back(tile);
        }
    }
}


Tile* Tilemap::getTileAtPos(int posX, int posY, int layer) {
    for(GameEntity* child : childs) {
        if(Tile* tile = dynamic_cast<Tile*>(child)) {
            if(tile->getLayer() == layer) {
                if(tile->getPosX() == posX && tile->getPosY() == posY) {
                    return tile;
                }
            }
        }
    }
    return NULL;
}


int Tilemap::getWidth() {
    return this->width;
}

int Tilemap::getHeight() {
    return this->height;
}

int Tilemap::getWidthInPixel() {
    return this->width*tileSize;
}

int Tilemap::getHeightinPixel() {
    return this->height*tileSize;
}

int Tilemap::getTileSize() {
    return this->tileSize;
}

string Tilemap::getMapPath() {
    return this->mapPath;
}
