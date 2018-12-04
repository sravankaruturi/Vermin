//
// Created by ant on 12/3/18.
//

#pragma once

#include <src/Entity.h>
#include "ResourceObject.h"

namespace v_game{

class Stone : public vermin::Entity, public ResourceObject{

public:

    explicit Stone(glm::vec3 _position);

    void Update(float _deltaTime);

    };

}
