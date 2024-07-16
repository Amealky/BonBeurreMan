//
//  Bomb.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//


#ifndef Bomb_hpp
#define Bomb_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Core/GameEntity.hpp"
#include "Explosion.hpp"

using namespace sf;
using namespace std;

class Bomb : public GameEntity {

    public:
        Bomb(string name);
        Bomb(string name, string spriteSheetPath, Explosion* explosion, float delayBeforeExplosion);
        ~Bomb();
        
        //Core
        void ready() override;
        void update() override;
        Explosion* generateExplosion(Map* map);
        void increaseExplosionDistance(int distanceBonus);

        //Getter
        Bomb* copy();
        Explosion* getExplosion();
        bool isActivated();
        bool isExploded();
        int getDelayBeforeExplosion();
        int getCurrentTimeBeforeExplosion();

        //Setter
        void activate();
        void explode();
        void setExplosion(Explosion* explosion);
        void setDelayBeforeExplosion(int delay);


    private:
        Explosion* explosion;
        bool activated;
        bool exploded;
        float delayBeforeExplosion;
        float currentTimeBeforeExplosion;

};
#endif
