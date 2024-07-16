#include "UIEditText.hpp"

UIEditText::UIEditText(float sizeX, float sizeY, int maxChar, int characterSize, 
                        Color textColor, string fontPath) {

    this->background = new RectangleShape({sizeX, sizeY});
    this->background->setFillColor(Color::Black);
    this->maxChar = maxChar;
    this->uiText = new UIText("", characterSize, textColor, fontPath);
}

UIEditText::~UIEditText() {
    if(background != NULL) {
        delete background;
    }
    if(uiText != NULL) {
        delete uiText;
    } 
}

void UIEditText::load() {
    this->uiText->load();
}

void UIEditText::draw(RenderWindow* window, int posX, int posY) {
    this->background->setPosition(posX, posY);
    window->draw(*this->background);
    this->uiText->draw(window, posX + marginX, posY +  this->uiText->getText()->getLocalBounds().height/2);
}

float UIEditText::getSizeX() {
    return this->sizeX;
}

float UIEditText::getSizeY() {
    return this->sizeY;
}

float UIEditText::getMarginX() {
    return this->marginX;
}

float UIEditText::getMaxChar() {
    return this->maxChar;
}

RectangleShape* UIEditText::getBackground() {
    return this->background;
}

UIText* UIEditText::getUIText() {
    return this->uiText;
}

void UIEditText::setSizeX(float sizeX) {
    this->sizeX = sizeX;
    this->background->setSize({this->sizeX, this->sizeY});
}

void UIEditText::setSizeY(float sizeY) {
    this->sizeY = sizeY;
    this->background->setSize({this->sizeX, this->sizeY});
}

void UIEditText::setMarginX(float marginX) {
    this->marginX = marginX;
}

void UIEditText::setMaxChar(float maxChar) {
    this->maxChar = maxChar;
}

void UIEditText::setBackgroundColor(Color color) {
    this->background->setFillColor(color);
}

void UIEditText::addChar(char c) {
    string newText = this->uiText->getText()->getString() + c;
    if(newText.size() <= this->maxChar) {
        this->uiText->getText()->setString(newText);
    }
}

void UIEditText::removeChar() {
    string newText = this->uiText->getText()->getString();
    if(newText.size() > 0) {
        newText.pop_back();
        this->uiText->getText()->setString(newText);
    }
}
