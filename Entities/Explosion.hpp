//
//  Explosion.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef Explosion_hpp
#define Explosion_hpp

#include "../Utils.hpp"
#include "Core/GameEntity.hpp"
#include "Map.hpp"
#include "ExplosionPart.hpp"


class Explosion : public GameEntity {

    public:
        Explosion(string name, string spriteSheetPath, int distance, int explosionDuration);
        ~Explosion();

        //Core
        void ready() override;
        void update() override;
        void generateExplosionLines(Map* map);

        //Getter
        Explosion* copy();
        int getDistance();
        int getExplosionDuration();
        int getCurrentTime();

        //Setter
        void setDistance(int distance);
        void setExplosionDuration(int duration);

    private:
        //Core
        void generateExplosionLine(EXPLOSION_SIDE endSide, int directionX, int directionY, Map* map);
        void generateExplosionCenter();
        bool generateExplosionPart(EXPLOSION_SIDE side, int partNumber, int directionX, int directionY, Map* map);
        
        int distance;
        int explosionDuration;
        int explosionCurrentTime;


};


#endif