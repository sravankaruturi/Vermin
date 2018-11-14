//
// Created by skk7174 on 11/12/2018.
//

#include "Building.h"

namespace v_game
{

	Building::Building(const unsigned _health)
		: Entity("building", "Medieval_House/Medieval_House.obj", "town_center", glm::vec3(-120, 0, -120), glm::vec3(150, 200, 200)), health(_health)
	{

		this->SetScale(glm::vec3(1 / 256.0f));

	}

}
