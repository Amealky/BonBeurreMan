#include "PhysicsServer.hpp"

PhysicsServer::PhysicsServer() {}

void PhysicsServer::checkPhysicalCollisions() {
    for(GameEntity* gameEntity : this->gameEntities) {
        recursivePhysicalCollision(gameEntity);
    }    
}

void PhysicsServer::checkTriggerCollisions() {
    for(GameEntity* gameEntity : this->gameEntities) {
        recursiveTriggerCollision(gameEntity);
    }    
}

//Check the eligibility of the first collider
void PhysicsServer::recursivePhysicalCollision(GameEntity* gameEntity) {
    if(!gameEntity) {
        return;
    }

    bool collisionHappen = false;


    //Check if the collider has a moveBody and a collider and its moving
    //If not no need to check for collision
    MoveBody* moveBody = gameEntity->getBody();
    Collider* collider = gameEntity->getCollider();
    if(moveBody != NULL && collider != NULL) {
        if(moveBody->getDirectionHorizontal() != 0 || moveBody->getDirectionVertical() != 0) {
            //Loop on the second entity of the screen
            for(GameEntity* otherGameEntity : this->gameEntities) {
                if(gameEntity != otherGameEntity) {
                    //We test if a collision happen on it or one of its childs
                    collisionHappen = recursivePhysicalCollision(gameEntity, otherGameEntity);
                    //If yes no need to test the other no move will be allowed
                    if(collisionHappen) {
                        break;
                    }
                }

            }
            //If no collision happen for this entity (regardless of his child) the entity object can move
            if(!collisionHappen) {
                gameEntity->applyMovement();
            }
            moveBody->setDirectionHorizontal(0);
            moveBody->setDirectionVertical(0);
        }

    }


    //Now we check the childs of this gameEntity
    for(GameEntity* gameEntityChild : gameEntity->getChilds()) {
        recursivePhysicalCollision(gameEntityChild);
    }

}


bool PhysicsServer::recursivePhysicalCollision(GameEntity* firstGameEntity, GameEntity* secondGameEntity) {
    if(!firstGameEntity || !secondGameEntity) {
        return false;
    }
    

    MoveBody* firstMoveBody = firstGameEntity->getBody();
    Collider* firstCollider = firstGameEntity->getCollider();

    Collider* secondCollider = secondGameEntity->getCollider();

    //If the second gameEntity has a collider
    if(secondCollider != NULL) {
        int directionHorizontal = firstMoveBody->getDirectionHorizontal();
        int directionVertical = firstMoveBody->getDirectionVertical();
        Rect<int>* firstRect = firstCollider->getColliderRect();
        int speed = firstMoveBody->getSpeed();
        int supposedNewXColliderPos = firstRect->left + speed * directionHorizontal;
        int supposedNewYColliderPos = firstRect->top + speed * directionVertical;
        Rect<int> supposedNewRect(supposedNewXColliderPos, supposedNewYColliderPos, firstRect->width, firstRect->height);

        Rect<int>* secondRect = secondCollider->getColliderRect();
    
        if(supposedNewRect.intersects(*secondRect)) {
            //Check masks
            if(contains(firstCollider->getPhysicsMasks(), secondCollider->getPhysicsLayer())) {
                //A collision happen
                return true;
            }    
        }
    }

    //Now we test the same firstGameEntity with all the childs of the seconds
    for(GameEntity* secondGameEntityChild : secondGameEntity->getChilds()) {
        if(firstGameEntity != secondGameEntityChild) {
            if(recursivePhysicalCollision(firstGameEntity, secondGameEntityChild)) {
                return true;
            }
        }
    }

    //If we reach that no collison happen with this entity or its childs
    return false;

}

void PhysicsServer::recursiveTriggerCollision(GameEntity* gameEntity) {
    if(!gameEntity) {
        return;
    }

    //Check if the collider exist and has a trigger mask
    //If not no need to continue
    Collider* collider = gameEntity->getCollider();
    if(collider != NULL) {
        if(!collider->getTriggerMasks().empty()) {
            for(GameEntity* otherGameEntity : this->gameEntities) {
                if(gameEntity != otherGameEntity) {
                    //We test if a collision happen on it or one of its childs
                    recursiveTriggerCollision(gameEntity, otherGameEntity);
                }
            }
        }
    }

    //Now we check the childs of this gameEntity
    for(GameEntity* gameEntityChild : gameEntity->getChilds()) {
        recursiveTriggerCollision(gameEntityChild);
    }

}


void PhysicsServer::recursiveTriggerCollision(GameEntity* firstGameEntity, GameEntity* secondGameEntity) {
    if(!firstGameEntity || !secondGameEntity) {
        return;
    }

    Collider* firstCollider = firstGameEntity->getCollider();

    Collider* secondCollider = secondGameEntity->getCollider();

    //If the second gameEntity has a collider
    if(secondCollider != NULL) {
        Rect<int>* firstRect = firstCollider->getColliderRect();
        Rect<int>* secondRect = secondCollider->getColliderRect();
        if(firstRect->intersects(*secondRect)) {
            //Check masks
            if(contains(firstCollider->getTriggerMasks(), secondCollider->getTriggerLayer())) {
                //A collision happen
                firstGameEntity->onCollisionHappening(secondGameEntity);
                secondGameEntity->onCollisionHappening(firstGameEntity);
            }    
        }
    }

    //Now we test the same firstGameEntity with all the childs of the seconds
    for(GameEntity* secondGameEntityChild : secondGameEntity->getChilds()) {
        if(firstGameEntity != secondGameEntityChild) {
            recursiveTriggerCollision(firstGameEntity, secondGameEntityChild);
        }
    }

}
