//
//  KeyboardController.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <stdio.h>
#include "IController.hpp"

using namespace sf;

class KeyboardController : public IController{
    public:
        virtual MappedEvent mapEvent(Event event);
        
};

#endif