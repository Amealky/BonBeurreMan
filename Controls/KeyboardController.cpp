#include "KeyboardController.hpp"


MappedEvent KeyboardController::mapEvent(Event event) {
 
    switch (event.type)
    {
        case Event::TextEntered: {
            if(event.text.unicode < 128) {
                char enteredChar = static_cast<char>(event.text.unicode);
                if (isdigit(enteredChar) || enteredChar == '.') {
                    return { INPUT_EVENT::NUMBER_ENTERED, enteredChar };
                }
            }

            return {INPUT_EVENT::NOKEY, 0};  
        }
        case Event::KeyPressed:
            switch(event.key.code){
                case Keyboard::Escape:
                    return {INPUT_EVENT::ESCAPE_PRESSED, 0};
                case Keyboard::Return:
                    return {INPUT_EVENT::ENTER_PRESSED, 0};
                case Keyboard::Up:
                    return {INPUT_EVENT::UP_PRESSED, 0};
                case Keyboard::Down:
                    return {INPUT_EVENT::DOWN_PRESSED, 0};
                case Keyboard::Left:
                    return {INPUT_EVENT::LEFT_PRESSED, 0};
                case Keyboard::Right:
                    return {INPUT_EVENT::RIGHT_PRESSED, 0};
                case Keyboard::BackSpace:
                    return {INPUT_EVENT::BACK_SPACE_PRESSED, 0};
                case Keyboard::B:
                    return {INPUT_EVENT::BOMB, 0};
                default:
                    return {INPUT_EVENT::NOKEY, 0};  
            }
            break;
        case Event::Closed:
            return {INPUT_EVENT::EXIT_PRESSED, 0};
            break;
        default:
            return {INPUT_EVENT::NOKEY, 0};           
    }

}
