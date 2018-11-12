//
// Created by skk7174 on 11/12/2018.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Building.h"
#include "GLShader.h"

namespace v_game
{
	
	enum class PlayerType
	{
		
		Human,
		Ai

	};

	class Player {


	private:

		unsigned int rWood = 0;
		unsigned int rStone = 0;

		PlayerType pType;

		glm::vec3 pColour;

		std::unique_ptr<Building> buildings;

		vermin::GLShader * shaderPointer;

	public:

		Player(glm::vec3 _startPosition, PlayerType _pType);

		void Update(float _deltaTime, float _totalTime);

		void Render();

		~Player() = default;

	};

}

#endif //GAME_PLAYER_H
