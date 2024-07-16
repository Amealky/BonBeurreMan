//
//  GameEntity.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef GameEntity_hpp
#define GameEntity_hpp

#include "Drawing/DynamicSprite.hpp"
#include "Drawing/DynamicSpriteListener.hpp"
#include "Drawing/UI/UIText.hpp"
#include "Drawing/UI/UIEditText.hpp"
#include "Physics/Collider.hpp"
#include "Physics/MoveBody.hpp"
#include "Audio/AudioSFX.hpp"


#include "../../Network/NetworkManager.hpp"

enum RENDER_MODE {UIVIEW, GAMEVIEW};

class GameEntity : public DynamicSpriteListener {

    public:
        GameEntity(string name);
        virtual ~GameEntity();

        //Core
        virtual void load();
        virtual void draw(RenderWindow* window, int posX, int posY);
        virtual void ready();
        virtual void update();
        virtual void onCollisionHappening(GameEntity* other);
        virtual void applyMovement();

        //Listeners
        virtual void onAnimationEnded(string animationName) override;
        

        //Getter
        string getName();
        float getPosX();
        float getPosY();
        int getLayer();
        bool isVisible();
        RENDER_MODE getRenderMode();
        vector<GameEntity*> getChilds();
        DynamicSprite* getSprite();
        UIText* getUIText();
        UIEditText* getUIEditText();
        Collider* getCollider();
        MoveBody* getBody(); 
        vector<AudioSFX*> getAudiosSfx();
        AudioSFX* getAudioSfxByName(string audioName);
        NetworkManager* getNetworkManager();

        //Setter
        void setName(string name);
        void setPosX(float posX);
        void setPosY(float posY);
        void setLayer(int layer);
        void setVisible(bool visible);
        void setRenderMode(RENDER_MODE renderMode);
        void addChild(GameEntity* gameEntity);
        void removeChild(GameEntity* gameEntity);
        void setSprite(DynamicSprite* sprite);
        void setUIText(UIText* uiText);
        void setUIEditText(UIEditText* uiEditText);
        void setCollider(Collider* collider);
        void setBody(MoveBody* body);
        void addAudioSfx(AudioSFX* sfx);
        void removeAudioSfx(AudioSFX* sfx);
        void setNetworkManager(NetworkManager* networkManager);

        //Static
        static bool compareByPosY(GameEntity* firstGameEntity, GameEntity* secondGameEntity);
        
    protected:
        string name;
        float posX;
        float posY;
        int layer;
        bool visible;
        RENDER_MODE renderMode;
        vector<GameEntity*> childs;
        
        DynamicSprite* sprite;
        UIText* uiText;
        UIEditText* uiEditText;
        Collider* collider;
        MoveBody* body;
        vector<AudioSFX*> audiosSfx;

        NetworkManager* networkManager;
};

 #endif