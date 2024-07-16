#ifndef Server_hpp
#define Server_hpp

#include "../Entities/Core/GameEntity.hpp"

using namespace std;

class Server {
    public:
    
        Server();

        //Setter
        void setGameEntities(vector<GameEntity*> gameEntities);
        void addGameEntity(GameEntity* gameEntity);
        void clearEntities();

    protected:
        vector<GameEntity*> gameEntities;
};


#endif