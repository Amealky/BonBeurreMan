#ifndef TileListener_hpp
#define TileListener_hpp

#include "../GameEntity.hpp"

class TileListener {
public:
    virtual void onCollisionHappeningOnTile(GameEntity* other) = 0;
};

#endif // EVENTLISTENER_HPP