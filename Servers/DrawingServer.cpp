#include "DrawingServer.hpp"

DrawingServer::DrawingServer(int layers) {
    this->layers = layers;
}

void DrawingServer::draw(RenderWindow* window, View* uiView, View* gameView) {
    sort(this->gameEntities.begin(), this->gameEntities.end(), GameEntity::compareByPosY);
    if(gameView != NULL) {
        window->setView(*gameView);
        for(int i = 0; i < layers; i++) {
            for(GameEntity* gameEntity : this->gameEntities) {
                if(gameEntity->isVisible()) {
                    recursiveDraw(window, gameEntity, i, RENDER_MODE::GAMEVIEW);
                } 
            }
        }
    }

    if(uiView != NULL) {
        window->setView(*uiView);
        for(int i = 0; i < layers; i++) {
            for(GameEntity* gameEntity : this->gameEntities) {
                if(gameEntity->isVisible()) {
                    recursiveDraw(window, gameEntity, i, RENDER_MODE::UIVIEW);
                }
            }
        }
    }
}

void DrawingServer::recursiveDraw(RenderWindow* window, GameEntity* gameEntity, int layer, RENDER_MODE renderMode) {
    if(!gameEntity) {
        return;
    }

    if(gameEntity->getRenderMode() == renderMode) {
        if(gameEntity->getLayer() == layer) {
            gameEntity->draw(window, gameEntity->getPosX(), gameEntity->getPosY());
        }
    }

    for(GameEntity* gameEntityChild : gameEntity->getChilds()) {
        recursiveDraw(window, gameEntityChild, layer, renderMode);
    }
}


int DrawingServer::getLayers() {
    return this->layers;
}

void DrawingServer::setLayers(int layers) {
    this->layers = layers;
}