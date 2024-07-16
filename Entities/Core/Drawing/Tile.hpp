//
//  Tile.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp


#include <SFML/Graphics.hpp>

#include "TileListener.hpp"
#include "../GameEntity.hpp"


using namespace sf;

class Tile : public GameEntity {

    public:
        Tile(string name);
        Tile(string name, string tilesetPath, int id);
        ~Tile();

        //Core
        void onCollisionHappening(GameEntity* other) override;
        
        //Getter
        int getId();

        //Setter
        void setTileListener(TileListener* tileListener);
    
    private:
        int id;
        TileListener* tileListener;


};

#endif