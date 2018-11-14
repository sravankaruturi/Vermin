//
// Created by skk7174 on 11/12/2018.
//

#include "Unit.h"

namespace v_game {

	Unit::Unit()
		: AnimatedEntity("Unit", "RTSDemo/HappyIdle.fbx", "unit")
	{

		this->SetScale(glm::vec3(1 / 32.0f));
		this->SetRotation(glm::vec3(0, 0, 0));

	}
}
