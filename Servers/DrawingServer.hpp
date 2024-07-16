//
//  DrawerServer.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef DrawingServer_hpp
#define DrawingServer_hpp

#include <SFML/Graphics.hpp>

#include "Server.hpp"
#include "../Entities/Core/GameEntity.hpp"


class DrawingServer : public Server {
    public:

        DrawingServer(int layers);
        ~DrawingServer(){};

        //Core
        void draw(RenderWindow* window, View* uiView, View* gameView);

        //Getter
        int getLayers();

        //Setter
        void setLayers(int layers);

    private:
        //Core
        void recursiveDraw(RenderWindow* window, GameEntity* gameEntity, int layer, RENDER_MODE renderMode);
        int layers;
        
};

#endif