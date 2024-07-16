#include "GameEntity.hpp"


GameEntity::GameEntity(string name) {
    this->name = name;
    this->posX = 0;
    this->posY = 0;
    this->layer = 0;
    this->visible = true;
    this->renderMode = RENDER_MODE::GAMEVIEW;
    this->sprite = NULL;
    this->uiText = NULL;
    this->uiEditText = NULL;
    this->collider = NULL;
    this->body = NULL;
    this->networkManager = NULL;
}

GameEntity::~GameEntity() {
    for(GameEntity* child : childs) {
        if(child != NULL) {
            delete child;
            child = NULL;
        }
    }
    childs.clear();

    if(sprite != NULL) {
        delete sprite;
        sprite = NULL;
    }

    if(uiText != NULL) {
        delete uiText;
        uiText = NULL;
    }

    if(uiEditText != NULL) {
        delete uiEditText;
        uiEditText = NULL;
    }

    if(collider != NULL) {
        delete collider;
        collider = NULL;
    }

    if(body != NULL) {
        delete body;
        body = NULL;
    }


    for(AudioSFX* audioSfx : audiosSfx) {
        if(audioSfx != NULL) {
            delete audioSfx;
            audioSfx = NULL;
        }
    }
    audiosSfx.clear();

}

void GameEntity::load() {
    if(sprite != NULL) {
        sprite->load();
    }
    if(uiText != NULL) {
        uiText->load();
    }
    if(uiEditText != NULL) {
        uiEditText->load();
    }
    ready();
}

void GameEntity::draw(RenderWindow* window, int posX, int posY) {
    if(sprite != NULL) {
        sprite->animate();
        sprite->draw(window, posX, posY);
    }
    if(uiText != NULL) {
        uiText->draw(window, posX, posY);
    }
    if(uiEditText != NULL) {
        uiEditText->draw(window, posX, posY);
    }
}

void GameEntity::ready() {}

void GameEntity::update() {
    //If there is a move body the gameobject is always following its position
    if(this->body != NULL) {
        this->posX = this->body->getPosX();
        this->posY = this->body->getPosY();
    }

    //If there is a collider the collider should follow the gameobject pos relatively to its own
    if(this->collider != NULL) {
        this->collider->relativeMove(this->posX, this->posY);
    }

}

void GameEntity::onCollisionHappening(GameEntity* other) {}

void GameEntity::applyMovement() {
    this->getBody()->move();
}

void GameEntity::onAnimationEnded(string animationName) {}


string GameEntity::getName() {
    return this->name;
}

float GameEntity::getPosX() {
    return this->posX;
}

float GameEntity::getPosY() {
    return this->posY;
}

int GameEntity::getLayer() {
    return this->layer;
}

bool GameEntity::isVisible() {
    return this->visible;
}

RENDER_MODE GameEntity::getRenderMode() {
    return this->renderMode;
}

vector<GameEntity*> GameEntity::getChilds() {
    return this->childs;
}

DynamicSprite* GameEntity::getSprite() {
    return this->sprite;
}

UIText* GameEntity::getUIText() {
    return this->uiText;
}

UIEditText* GameEntity::getUIEditText() {
    return this->uiEditText;
}

Collider* GameEntity::getCollider() {
    return this->collider;
}

MoveBody* GameEntity::getBody() {
    return this->body;
}

vector<AudioSFX*> GameEntity::getAudiosSfx() {
    return this->audiosSfx;
}

AudioSFX* GameEntity::getAudioSfxByName(string name) {
    for(AudioSFX* audioSfx : this->audiosSfx) {
        if(audioSfx->getName() == name) {
            return audioSfx;
        }
    }
    return NULL;
}

NetworkManager* GameEntity::getNetworkManager() {
    return this->networkManager;
}

void GameEntity::setName(string name) {
    this->name = name;
}

void GameEntity::setPosX(float posX) {
    this->posX = posX;
}

void GameEntity::setPosY(float posY) {
    this->posY = posY;
}

void GameEntity::setLayer(int layer) {
    this->layer = layer;
}

void GameEntity::setVisible(bool visible) {
    this->visible = visible;
}

void GameEntity::setRenderMode(RENDER_MODE renderMode) {
    this->renderMode = renderMode;
}

void GameEntity::addChild(GameEntity* gameEntity) {
    this->childs.push_back(gameEntity);
}

void GameEntity::removeChild(GameEntity* gameEntity) {
    auto it = std::remove(this->childs.begin(), this->childs.end(), gameEntity);
    this->childs.erase(it, this->childs.end());
}

void GameEntity::setSprite(DynamicSprite* sprite) {
    this->sprite = sprite;
    this->sprite->setListener(this);
}

void GameEntity::setUIText(UIText* uiText) {
    this->uiText = uiText;
}

void GameEntity::setUIEditText(UIEditText* uiEditText) {
    this->uiEditText = uiEditText;
}

void GameEntity::setCollider(Collider* collider) {
    this->collider = collider;
}

void GameEntity::setBody(MoveBody* body) {
    this->body = body;
}

void GameEntity::addAudioSfx(AudioSFX* sfx) {
    this->audiosSfx.push_back(sfx);
}

void GameEntity::removeAudioSfx(AudioSFX* sfx) {
    auto it = std::remove(this->audiosSfx.begin(), this->audiosSfx.end(), sfx);
    this->audiosSfx.erase(it, this->audiosSfx.end());
}

void GameEntity::setNetworkManager(NetworkManager* networkManager) {
    this->networkManager = networkManager;
    for(GameEntity* child: this->childs) {
        child->setNetworkManager(networkManager);
    }
}

bool GameEntity::compareByPosY(GameEntity* firstGameEntity, GameEntity* secondGameEntity) {
    return firstGameEntity->getPosY() < secondGameEntity->getPosY();
}