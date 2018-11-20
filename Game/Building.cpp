//
// Created by skk7174 on 11/12/2018.
//

#include "Building.h"
#include <time.h>

namespace v_game
{
	float Building::GetCurrentHPPerc()
	{
		return ((float)health / maxHealth);
	}

	Building::Building(BuildingType _type, glm::vec3 _position)
		: Entity("building", "Medieval_House/Medieval_House.obj", "town_center", glm::vec3(-120, 0, -120), glm::vec3(150, 200, 200))
	{
		switch (_type)
		{
		case BuildingType::towncenter:
			health = 1000;
			break;
		case BuildingType::barracks:
			health = 600;
			break;
		case BuildingType::siegefactory:
			health = 800;
			break;
		}

		this->SetScale(glm::vec3(1 / 256.0f));
		this->SetPosition(_position);

		// Set the spawn points based on the Current Position.

		this->spawnPoints.clear();
		this->spawnPoints.reserve(4);
		this->spawnPoints.emplace_back(glm::vec3(this->position.x + 1, this->position.y, this->position.z));
		this->spawnPoints.emplace_back(glm::vec3(this->position.x - 1, this->position.y, this->position.z));
		this->spawnPoints.emplace_back(glm::vec3(this->position.x, this->position.y, this->position.z + 1));
		this->spawnPoints.emplace_back(glm::vec3(this->position.x, this->position.y, this->position.z - 1));

	}

	glm::vec3 Building::GetRandomSpawnLocation()
	{
		srand(time(NULL));
		int test = rand() % this->spawnPoints.size();
		return this->spawnPoints[test];
	}
}
