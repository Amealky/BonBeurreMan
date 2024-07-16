//
//  DynamicSpriteListener.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//


#ifndef DynamicSpriteListener_hpp
#define DynamicSpriteListener_hpp

#include <string>

using namespace std;

class DynamicSpriteListener {
    public:
        virtual void onAnimationEnded(string animationName) = 0;
};

#endif