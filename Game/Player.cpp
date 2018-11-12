//
// Created by skk7174 on 11/12/2018.
//

#include "Player.h"
#include "AssetManager.h"

namespace v_game
{

	Player::Player(glm::vec3 _startPosition, PlayerType _pType)
		: pType(_pType)
	{
		// Let us give some wood and stone to the Player.
		rWood = 100;
		rStone = 100;

		pColour = (pType == PlayerType::Human) ? glm::vec3(1, 0, 0) : glm::vec3(0, 0, 1);

		// Add One Building.
		this->buildings = std::make_unique<Building>(500);
		this->buildings->SetPosition(_startPosition);

		shaderPointer = ASMGR.shaders.at("town_center").get();

	}

	void Player::Update(float _deltaTime, float _totalTime)
	{

		this->buildings->Update(_deltaTime);

	}

	void Player::Render()
	{
		shaderPointer->use();
		shaderPointer->setVec4("u_PlayerColour", pColour.x, pColour.y, pColour.z, 0.3);
		this->buildings->Render();
	}
}
