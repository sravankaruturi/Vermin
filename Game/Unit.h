//
// Created by skk7174 on 11/12/2018.
//

#ifndef GAME_UNIT_H
#define GAME_UNIT_H
#include "AnimatedEntity.h"
#include "../Engine/Terrain.h"


namespace v_game {

	enum class UnitType
	{

		villager,
		warrior,
		catapult

	};

	class Unit : public vermin::AnimatedEntity {

	public:

		Unit();
		~Unit() = default;

		void Update(float _deltaTime, vermin::Terrain * _terrain);

	protected:
		/* Pathing Stuff */
		std::vector<vermin::MapTile *> path;
		float totalTimeCounterForPathing = 0;
		float movementSpeed = 5.0f;
	};

}

#endif //GAME_UNIT_H
