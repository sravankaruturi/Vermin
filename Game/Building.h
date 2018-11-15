//
// Created by skk7174 on 11/12/2018.
//

#ifndef GAME_BUILDING_H
#define GAME_BUILDING_H

#include "../Engine/Entity.h"

namespace v_game
{

	enum class BuildingType{
		towncenter,
		barracks,
		siegefactory
	};

	class Building : public vermin::Entity{

	private:

		unsigned int health = 0;

		glm::vec3 spawnPoint;

	public:

		explicit Building(unsigned _health, BuildingType _type, glm::vec3 _spawnPoint, glm::vec3 _position);

		~Building() = default;

	};

}


#endif //GAME_BUILDING_H
