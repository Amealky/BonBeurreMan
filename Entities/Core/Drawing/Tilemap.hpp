//
//  Tilemap.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//


#ifndef Tilemap_hpp
#define Tilemap_hpp

#include <SFML/Graphics.hpp>

#include "Tile.hpp"
#include "TileListener.hpp"
#include "../GameEntity.hpp"
#include "../../../Utils.hpp"

using namespace std;

class Tilemap : public GameEntity, TileListener {

    public:
        Tilemap(string name, string mapPath, string tilesetPath);
        ~Tilemap();

        //Core
        void ready() override;
        
        //Listener
        virtual void onCollisionHappeningOnTile(GameEntity* other) override {};

        //Getter
        Tile* getTileAtPos(int posX, int posY, int layer);
        int getWidth();
        int getHeight();
        int getWidthInPixel();
        int getHeightinPixel();
        int getTileSize();
        string getMapPath();


    private:
        int width;
        int height;
        int tileSize;
        string mapPath;

};

#endif