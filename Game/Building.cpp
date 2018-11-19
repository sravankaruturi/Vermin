//
// Created by skk7174 on 11/12/2018.
//

#include "Building.h"

namespace v_game
{
	float Building::GetCurrentHPPerc()
	{
		return ((float)health / maxHealth);
	}

	Building::Building(unsigned _health, BuildingType _type, glm::vec3 _spawnPoint, glm::vec3 _position)
		: Entity("building", "Medieval_House/Medieval_House.obj", "town_center", glm::vec3(-120, 0, -120), glm::vec3(150, 200, 200)), health(_health), spawnPoint(_spawnPoint)
	{

		this->SetScale(glm::vec3(1 / 256.0f));
		this->SetPosition(_position);

	}

}
