//
// Created by skk7174 on 11/12/2018.
//

#ifndef GAME_UNIT_H
#define GAME_UNIT_H
#include "AnimatedEntity.h"

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

	};

}

#endif //GAME_UNIT_H
