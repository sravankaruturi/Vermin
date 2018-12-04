//
// Created by ant on 12/3/18.
//

#include <src/LoggingManager.h>
#include "Stone.h"

namespace v_game{


    Stone::Stone(glm::vec3 _position)
    : Entity("Tree", "Medieval_House/Medieval_House.obj", "town_center", glm::vec3(-120, 0, -120), glm::vec3(150, 200, 200)), ResourceObject(100)
    {
        entityType = 4;
        this->SetScale(glm::vec3(1/512.0f));
        this->SetPosition(_position);
        LOGGER.AddToLog(std::string("Created a new Stone, with resource value: ") + std::string("%d", this->resourceAmount) );
    }

    void Stone::Update(float _deltaTime) {

        if ( this->resourceAmount <= 0.0f ){
            this->gPlay.active = false;
        }

        Entity::Update(_deltaTime);
    }
}