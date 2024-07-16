//
//  Player.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include "Core/GameEntity.hpp"
#include "Bomb.hpp"
#include "Bonus.hpp"


using namespace std;
using namespace sf;

class Player : public GameEntity {
    
    public:
        Player(string name, string spriteSheetPath, int numero, int pv, Bomb* bomb, int bombsCapacityMax, int bombsRefreshDelay);
        ~Player();

        //Core
        void ready() override;
        void update() override;
        void onCollisionHappening(GameEntity* other) override;
        void applyMovement() override;
        void onAnimationEnded(string animationName) override;
        Bomb* launchBomb();
        void moveHorizontally(int direction);
        void moveVertically(int direction);
        void setMoveAnimation(int horizontal, int vertical);
        void setDeadState();
        bool isDead();

        //Network
        void askServerForMove(int horizontal, int vertical);
        void notifyMovementToClients();
        void askServerForPuttingBomb();
        void notifyBombLaunchedToClients();
        void notifyDeadToClients();

        //Getter
        int getNumero();
        int getPv();
        Bomb* getBomb();
        int getBombsCapacity();
        int getBombsRefreshDelay();
        bool canLaunchBomb();
        int getFeetPosY();

        //Setter
        void setNumero(int numero);
        void setPv(int pv);
        
    private:
        //General
        int numero;
        int pv;

        //Bombs
        Bomb* bomb;
        int bombsCapacity;
        int bombsCapacityMax;
        int bombsRefreshDelay;
        int bombsRefreshCurrentTime;
        bool bombsRefreshRunning;

        
    
};
#endif
