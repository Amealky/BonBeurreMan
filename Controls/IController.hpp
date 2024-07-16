//
//  IController.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef IController_hpp
#define IController_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

enum class INPUT_EVENT {NOKEY, NUMBER_ENTERED, BACK_SPACE_PRESSED, ESCAPE_PRESSED,
                        BOMB, 
                        UP_PRESSED, LEFT_PRESSED, RIGHT_PRESSED, DOWN_PRESSED,
                        UP_RELEASED, LEFT_RELEASED, RIGHT_RELEASED, DOWN_RELEASED, 
                        EXIT_PRESSED, ENTER_PRESSED};

struct MappedEvent {
    INPUT_EVENT eventType;
    char c;
};

class IController {
    
    public:
        virtual ~IController() {};
        virtual MappedEvent mapEvent(Event event) = 0;
};

#endif 
