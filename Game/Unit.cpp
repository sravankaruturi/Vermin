//
// Created by skk7174 on 11/12/2018.
//

#include "Unit.h"

namespace v_game {

	Unit::Unit()
		: AnimatedEntity("Unit", "RTSDemo/HappyIdle.fbx", "unit", glm::vec3(-10, 0, -10), glm::vec3(10, 50, 10))
	{

		this->SetScale(glm::vec3(1 / 64.0f));
		this->SetRotation(glm::vec3(0, 0, 0));

	}
}
