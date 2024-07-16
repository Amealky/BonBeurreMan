//
//  Map.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <memory>

#include <SFML/Graphics.hpp>
#include "Core/Drawing/Tilemap.hpp"
#include "ExplosionPart.hpp"
#include "Bonus.hpp"
#include "../Utils.hpp"


using namespace std;
using namespace sf;

enum class TILES { EMPTY = 0, TOP_WALL = 1, GROUND = 2, LEFT_WALL = 3,
                   RIGHT_WALL = 4, BOTTOM_WALL = 5, TOP_LEFT_CORNER = 6,
                   TOP_RIGHT_CORNER = 7, BOTTOM_LEFT_CORNER = 8, BOTTOM_RIGHT_CORNER = 9,
                   PILLAR = 10, DESTRUCTIBLE_WALL = 11,  DESTRUCTIBLE_WALL_BROKEN = 12};

class Map : public Tilemap {

    public:
        Map(string name, string mapPath, string tilesetPath);
        ~Map();

        //Core
        void ready() override;
        void update() override;
        void onCollisionHappeningOnTile(GameEntity* other) override;
        void centerGameEntity(GameEntity* gameEntity);
        bool isTileIsBlocker(Tile* tile);
        void destroyTile(Tile* tileToDestroy);
        void generateBonus(bool shouldGenerate, int posX, int posY);

        //Network
        void notifyDestructionToClients(int tilePosX, int tilePosY);
        void notifyBonusAppearToClients(int bonusPosX, int bonusPosY);

    
};

#endif
