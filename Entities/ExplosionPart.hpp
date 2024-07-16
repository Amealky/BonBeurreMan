//
//  ExplosionPart.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef ExplosionPart_hpp
#define ExplosionPart_hpp

#include "Core/GameEntity.hpp"
#include "Map.hpp"

enum class EXPLOSION_SIDE { VERTICAL = 0, HORIZONTAL = 4, END_UP = 8, END_LEFT = 12, 
                   END_RIGHT = 16, END_DOWN = 20, CENTER = 24 };


class ExplosionPart : public GameEntity {
    public:
        ExplosionPart(string name, string spriteSheetPat, EXPLOSION_SIDE side);
        ~ExplosionPart();

        //Core
        void ready() override;

        //Getter
        EXPLOSION_SIDE getExplosionSide();

        //Setter
        void setExplosionSide(EXPLOSION_SIDE side);

    private:
        EXPLOSION_SIDE side;



};


#endif