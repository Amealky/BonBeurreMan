//
//  PhysicsServer.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef PhysicsServer_hpp
#define PhysicsServer_hpp

#include "Server.hpp"
#include "../Utils.hpp"
#include "../Entities/Core/GameEntity.hpp"

class PhysicsServer : public Server {
    public:

        PhysicsServer();
        ~PhysicsServer(){};

        //Core
        void checkPhysicalCollisions();
        void checkTriggerCollisions();

    private:
        //Core
        void recursivePhysicalCollision(GameEntity* gameEntity);
        bool recursivePhysicalCollision(GameEntity* firstGameEntity, GameEntity* secondGameEntity);
        void recursiveTriggerCollision(GameEntity* gameEntity);
        void recursiveTriggerCollision(GameEntity* firstGameEntity, GameEntity* secondGameEntity);

};

#endif