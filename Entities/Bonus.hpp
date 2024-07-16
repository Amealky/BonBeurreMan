//
//  Bonus.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef Bonus_hpp
#define Bonus_hpp

#include "../Utils.hpp"
#include "Core/GameEntity.hpp"

class Bonus : public GameEntity {

    public:
        Bonus(string name, string spriteSheetPath, int distanceBonus);
        ~Bonus();
        
        //Core
        void ready() override;
        
        //Getter
        int getDistanceBonus();
        bool isUsed();

        //Setter
        void setDistanceBonus(int distanceBonus);
        void setUsed(bool used);

    private:
        int distanceBonus;
        bool used;
};

#endif