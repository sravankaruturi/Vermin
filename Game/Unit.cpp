//
// Created by skk7174 on 11/12/2018.
//

#include "Unit.h"

namespace v_game {

	Unit::Unit()
		: AnimatedEntity("Unit", "RTSDemo/HappyIdle.fbx", "bob_lamp")
	{

		this->SetScale(glm::vec3(1 / 128.0f));

	}
}
