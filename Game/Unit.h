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

	enum class AnimType
	{
		
		idle,
		walking,
		death

	};

	const std::string animation_names[3][3] = {
		{
			"Worker_Happy_Idle",
			"Worker_Walking",
			"Worker_Dying",
		},
		{
			"Knight_Happy_Idle",
			"Knight_Walking",
			"Knight_Dying",
		},
		{
			"Catapult_Happy_Idle",
			"Catapult_Walking",
			"Catapult_Dying",
		}
	};

	class Unit : public vermin::AnimatedEntity {

	public:

		explicit Unit(UnitType _type);
		~Unit() = default;

		void Update(float _deltaTime, vermin::Terrain * _terrain);

	protected:
		/* Pathing Stuff */
		std::vector<vermin::MapTile *> path;
		float totalTimeCounterForPathing = 0;
		float movementSpeed = 2.0f;

		std::string idleObjectName;
		std::string walkObjectName;
		std::string deathObjectName;

	};

}

#endif //GAME_UNIT_H
