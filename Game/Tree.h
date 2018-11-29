//
// Created by Sravan Karuturi on 11/28/18.
//

#pragma once

#include <src/Entity.h>
#include "ResourceObject.h"

namespace v_game{

	class Tree : public vermin::Entity, public ResourceObject{

	public:
		explicit Tree(glm::vec3 _position);

		void MineResources(int _amount) override {

			this->resourceAmount -= _amount;

		}

	};

}

