#include "UIText.hpp"

UIText::UIText(string textValue, int characterSize, Color textColor, string fontPath) {
    this->text = new Text();
    this->font = new Font();
    this->text->setString(textValue);
    this->text->setCharacterSize(characterSize);
    this->text->setFillColor(textColor);
    this->fontPath = fontPath;
}

UIText::~UIText() {
    if(text != NULL) {
        delete text;
    }
    
    if(font != NULL) {
        delete font;
    }
}


void UIText::load() {
    if (this->font->loadFromFile(getFontPath())) {
            this->text->setFont(*this->font);
    } else {
        throw runtime_error("Error while loading font : " + getFontPath());
    }
}

void UIText::draw(RenderWindow* window, int posX, int posY) {
    this->text->setPosition(posX, posY);
    window->draw(*this->text);
}

Text* UIText::getText() {
    return this->text;
}

string UIText::getTextValue() {
    return this->text->getString();
}

Font* UIText::getFont() {
    return this->font;
}

string UIText::getFontPath() {
    return this->fontPath;
}

void UIText::setText(Text* text) {
    this->text = text;
}

void UIText::setTextValue(string textValue) {
    this->text->setString(textValue);
}

void UIText::setFont(Font* font) {
    this->font = font;
}

void UIText::setFontPath(string fontPath) {
    this->fontPath = fontPath;
}

void UIText::setColor(Color color) {
    this->text->setFillColor(color);
}