//
//  DynamicSprite.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//


#ifndef DynamicSprite_hpp
#define DynamicSprite_hpp

#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "DynamicSpriteListener.hpp"

using namespace std;
using namespace sf;

class DynamicSprite {

    public:
        DynamicSprite(string spriteSheetPath);
        DynamicSprite(string spriteSheetPath, int sizeX, int sizeY, int frames, int animationDelay);
        ~DynamicSprite();

        //Core
        void load();
        void draw(RenderWindow* window, int posX, int posY);
        void animate();

        //Getter
        string getSpriteSheetPath();
        Texture* getSpriteSheet();
        Sprite*  getSprite();
        int getSizeX();
        int getSizeY();
        bool isFlipped();
        unordered_map<string, int> getAnimations();
        int getStartingFrameOfAnimation(string animationName);
        string getCurrentAnimationName();
        int getFrames();
        int getCurrentFrame();
        int getAnimationDelay();
        int getAnimationCurrentTime();
        bool isAnimationRunning();
        bool isLooping();

        //Setter
        void setSpriteSheetPath(string path);
        void setSpriteSheet(sf::Texture *spriteSheet);
        void setSprite(sf::Sprite *sprite);
        void setSizeX(int sizeX);
        void setSizeY(int sizeY);
        void setFlipped(bool flipped);
        void addAnimation(string animationName, int startingFrame);
        void removeAnimation(string animationName);
        void setCurrentAnimation(string animationName);
        void setFrames(int frames);
        void setCurrentFrame(int frame);
        void setAnimationDelay(int delay);
        void setAnimationCurrentTime(int currentTime);
        void setAnimationRunning(bool animationRunning);
        void setLooping(bool looping);
        void setListener(DynamicSpriteListener* listener);


    private:
        //Visual
        string spriteSheetPath;
        Texture* spriteSheet;
        Sprite* sprite;
        int startX;
        int startY;
        int sizeX;
        int sizeY;
        bool flipped;

        //Animation
        unordered_map<string, int> animationsStartFrames;
        string currentAnimation;
        int frames;
        int currentFrame;
        int animationDelay;
        int animationCurrentTime;
        bool animationRunning;
        bool looping;
        DynamicSpriteListener* listener;



};

#endif