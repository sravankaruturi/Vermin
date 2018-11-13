//
// Created by skk7174 on 11/12/2018.
//

#include "Player.h"
#include "AssetManager.h"

namespace v_game
{

	Player::Player(glm::vec3 _startPosition, PlayerType _pType)
		: pType(_pType), baseStartPosition(_startPosition)
	{

		villagerStartPosition = baseStartPosition;
		villagerStartPosition.x += 1.5;
		villagerStartPosition.z -= 1.5;

		// Let us give some wood and stone to the Player.
		rWood = 100;
		rStone = 100;

		pColour = (pType == PlayerType::Human) ? glm::vec3(1, 0, 0) : glm::vec3(0, 0, 1);

		// Add One Building.
		this->buildings.emplace_back(std::make_unique<Building>(500));
		this->buildings[0]->SetPosition(baseStartPosition);

		this->units.emplace_back(std::make_unique<Unit>());
		this->units[0]->SetPosition(villagerStartPosition);

		shaderPointer = ASMGR.shaders.at("town_center").get();

	}

	void Player::Update(float _deltaTime, float _totalTime)
	{

		for (auto& it : buildings) {
			it->Update(_deltaTime);
		}

		for (auto& it : units) {
			it->Update(_deltaTime);
			it->PlayAnimation(_deltaTime, _totalTime);
		}
		

	}

	void Player::Render()
	{
		shaderPointer->use();
		shaderPointer->setVec4("u_PlayerColour", pColour.x, pColour.y, pColour.z, 0.3);
		
		for (auto& it : buildings) {
			it->Render();
		}

		for (auto& it : units) {
			it->Render();
		}

	}
}
