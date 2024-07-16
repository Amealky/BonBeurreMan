//
//  MoveBody.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef MoveBody_hpp
#define MoveBody_hpp


class MoveBody {

    public:
        MoveBody();
        MoveBody(int posX, int posY, int speed);
        ~MoveBody();

        //Core
        void move();

        //Getter
        int getPosX();
        int getPosY();
        int getSpeed();
        int getDirectionHorizontal();
        int getDirectionVertical();

        //Setter
        void setPosX(int posX);
        void setPosY(int posY);
        void setSpeed(int speed);
        void setDirectionHorizontal(int directionHorizontal);
        void setDirectionVertical(int directionVertical);
        
    private:
        int posX;
        int posY;
        int speed;
        int directionHorizontal;
        int directionVertical;

};


#endif