#include "DynamicSprite.hpp"

DynamicSprite::DynamicSprite(string spriteSheetPath) {
    this->spriteSheetPath = spriteSheetPath;
    this->spriteSheet = new Texture();
    this->sprite = new Sprite();
    startX = 0;
    startY = 0;
    this->sizeX = 0;
    this->sizeY = 0;
    this->flipped = false;
    this->addAnimation("NONE", 0);
    this->currentAnimation = "NONE";
    this->frames = 1;
    this->currentFrame = 0;
    this->animationDelay = 0;
    this->animationCurrentTime = 0;
    this->currentFrame = 0;
    this->animationRunning = false;
    this->looping = false;
    listener = NULL;

}

DynamicSprite::DynamicSprite(string spriteSheetPath, int sizeX, int sizeY, int frames, int animationDelay) {
    this->spriteSheetPath = spriteSheetPath;
    this->spriteSheet = new Texture();
    this->sprite = new Sprite();
    startX = 0;
    startY = 0;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->flipped = false;
    this->addAnimation("NONE", 0);
    this->currentAnimation = "NONE";
    this->frames = frames;
    this->animationDelay = animationDelay;
    this->animationCurrentTime = animationDelay;
    this->currentFrame = 0;
    this->animationRunning = false;
    this->looping = false;
    listener = NULL;
}

DynamicSprite::~DynamicSprite() {
    if(spriteSheet != NULL) {
        delete spriteSheet;
        spriteSheet = NULL;
    }

    if(sprite != NULL) {
        delete sprite;
        sprite = NULL;
    }
    
    
}

void DynamicSprite::load() {
    if(spriteSheet->loadFromFile(getSpriteSheetPath())){
        sprite->setTexture(*getSpriteSheet());
    } else {
        throw runtime_error("Error while loading tileset : " + getSpriteSheetPath());
    }
}

void DynamicSprite::draw(RenderWindow* window, int posX, int posY) { 
    int startingFrameOfAnimation = getStartingFrameOfAnimation(currentAnimation);
    int startX = (sizeX * currentFrame) + (sizeX * startingFrameOfAnimation);
    sprite->setPosition(posX, posY);
    sprite->setTextureRect(IntRect(startX, 0, sizeX, sizeY));
    window->draw(*getSprite());
}

void DynamicSprite::animate() {
    if(animationCurrentTime <= 0) {
        animationCurrentTime = animationDelay;
        currentFrame++;
        if(currentFrame >= frames) {
            currentFrame = 0;
            if(!looping) {
                animationRunning = false;
                listener->onAnimationEnded(currentAnimation);
            }
        }
    }

    if(animationRunning) {
        animationCurrentTime--;
    }
}

string DynamicSprite::getSpriteSheetPath() {
    return this->spriteSheetPath;
}

Texture* DynamicSprite::getSpriteSheet() {
    return this->spriteSheet;
}

Sprite* DynamicSprite::getSprite() {
    return this->sprite;
}

int DynamicSprite::getSizeX() {
    return this->sizeX;
}

int DynamicSprite::getSizeY() {
    return this->sizeY;
}

bool DynamicSprite::isFlipped() {
    return this->flipped;
}

unordered_map<string, int> DynamicSprite::getAnimations() {
    return this->animationsStartFrames;
}

int DynamicSprite::getStartingFrameOfAnimation(string animationName) {
    return this->animationsStartFrames[animationName];
}

string DynamicSprite::getCurrentAnimationName() {
    return this->currentAnimation;
}

int DynamicSprite::getFrames() {
    return this->frames;
}

int DynamicSprite::getCurrentFrame() {
    return this->currentFrame;
}

int DynamicSprite::getAnimationDelay() {
    return this->animationDelay;
}

int DynamicSprite::getAnimationCurrentTime() {
    return this->animationCurrentTime;
}

bool DynamicSprite::isAnimationRunning() {
    return this->animationRunning;
}

bool DynamicSprite::isLooping() {
    return this->looping;
}

void DynamicSprite::setSpriteSheetPath(string path) {
    this->spriteSheetPath = path;
}

void DynamicSprite::setSpriteSheet(Texture* spriteSheet) {
    this->spriteSheet = spriteSheet;
}

void DynamicSprite::setSprite(Sprite* sprite) {
    this->sprite = sprite;
}

void DynamicSprite::setSizeX(int sizeX) {
    this->sizeX = sizeX;
}

void DynamicSprite::setSizeY(int sizeY) {
    this->sizeY = sizeY;
}

void DynamicSprite::setFlipped(bool flipped) {
    this->flipped = flipped;
}

void DynamicSprite::addAnimation(string animationName, int startingFrame) {
    this->animationsStartFrames[animationName] = startingFrame;
}

void DynamicSprite::removeAnimation(string animationName) {
    this->animationsStartFrames.erase(animationName);
}

void DynamicSprite::setCurrentAnimation(string animationName) {
    this->animationCurrentTime = this->animationDelay;
    this->animationRunning = true;
    this->currentAnimation = animationName;
}

void DynamicSprite::setFrames(int frames) {
    this->frames = frames;
}

void DynamicSprite::setCurrentFrame(int frame) {
    this->currentFrame = frame;
}

void DynamicSprite::setAnimationDelay(int delay) {
    this->animationDelay = delay;
}

void DynamicSprite::setAnimationCurrentTime(int currentTime) {
    this->animationCurrentTime = currentTime; 
}

void DynamicSprite::setAnimationRunning(bool animationRunning) {
    this->animationRunning = animationRunning;
}

void DynamicSprite::setLooping(bool looping) {
    this->looping = looping;
}

void DynamicSprite::setListener(DynamicSpriteListener* listener) {
    this->listener = listener;
}