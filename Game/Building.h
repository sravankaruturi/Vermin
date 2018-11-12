//
// Created by skk7174 on 11/12/2018.
//

#ifndef GAME_BUILDING_H
#define GAME_BUILDING_H

#include "../Engine/Entity.h"

namespace v_game
{
	
	class Building : public vermin::Entity{

	private:

		unsigned int health = 0;

	public:

		explicit Building(unsigned _health);

		~Building() = default;

	};

}


#endif //GAME_BUILDING_H
