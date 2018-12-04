//
// Created by Sravan Karuturi on 11/28/18.
//

#pragma once

#include "ResourceObject.h"
#include <src/Entity.h>

namespace v_game{

	class Tree : public vermin::Entity, public ResourceObject{

	public:
		explicit Tree(glm::vec3 _position);

		void Update(float _deltaTime);

	};

}

