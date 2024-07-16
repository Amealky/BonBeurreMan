//
//  Collider.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef Collider_hpp
#define Collider_hpp


#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Collider {

    public:
        Collider();
        Collider(Rect<int>* rect, int posX, int posY);
        ~Collider();

        //Core
        void relativeMove(int parentPosX, int parentPosY);

        //Getter
        Rect<int>* getColliderRect();
        int getRelativePosX();
        int getRelativePosY();
        vector<string> getPhysicsLayer();
        vector<string> getTriggerLayer();
        vector<string> getPhysicsMasks();
        vector<string> getTriggerMasks();

        //Setter
        void setColliderRect(Rect<int>* rect);
        void setRelativePosX(int relativePosX);
        void setRelativePosY(int relativePosY);
        void addPhysicsLayer(string layer);
        void addTriggerLayer(string layer);
        void addPhysicsMask(string mask);
        void addTriggerMask(string mask);
        void removePhysicsLayer(string layer);
        void removeTriggerLayer(string layer);
        void removePhysicsMask(string mask);
        void removeTriggerMask(string mask);

    private:
        Rect<int>* rect;
        int relativePosX;
        int relativePosY;
        vector<string> physicsLayers;
        vector<string> triggerLayers;
        vector<string> physicsMasks;
        vector<string> triggerMasks;
};
#endif
