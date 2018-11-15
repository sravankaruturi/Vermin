#pragma once

#include "../Engine/library.h"
#include "../Engine/Terrain.h"
#include "glm/detail/type_mat.hpp"


#include "GamePlayManager.h"
#include "Building.h"
#include "Unit.h"

namespace v_game {

	enum class PlayerType
	{
		Human,
		Ai
	};

	struct Player{

		unsigned int rWood = 0;
		unsigned int rStone = 0;

		PlayerType pType = PlayerType::Ai;

		glm::vec4 pColour{0 ,0, 1, 0.3};

		std::vector<std::shared_ptr<Building>> buildings{};
		std::vector<std::shared_ptr<Unit>> units{};

		glm::vec3 baseStartPosition{0};
		glm::vec3 villagerStartPosition{0};

		Player() = default;

		Player(glm::vec3 _baseStartPosition, PlayerType _pType){

			baseStartPosition = _baseStartPosition;

			pType = _pType;

			villagerStartPosition = baseStartPosition;
			villagerStartPosition.x += 1.5;
			villagerStartPosition.z -= 1.5;

			// Let us give some wood and stone to the Player.
			rWood = 100;
			rStone = 100;

			pColour = (pType == PlayerType::Human) ? glm::vec4(1, 0, 0, 0.3) : glm::vec4(0, 0, 1, 0.3);

			// Add One Building.
			this->buildings.emplace_back(std::make_shared<Building>(1000, BuildingType::towncenter, baseStartPosition, villagerStartPosition));

			this->units.emplace_back(std::make_shared<Unit>(UnitType::villager));
			this->units[0]->SetPosition(villagerStartPosition);

			villagerStartPosition.x -= 1.5;
			villagerStartPosition.z += 1.5;

		}

	};

	class GameScene : public vermin::Scene{

	private:

		/* GUI Variables */
		bool displayLogWindow = false;

		/* Camera Constraints */
		glm::vec4 camConstraints{1.f, 23.f, 1.f, 23.f};

		std::shared_ptr<vermin::Terrain> gameTerrain;

		vermin::Grid grid;
		glm::mat4 projectionMatrix;

		std::unique_ptr<GamePlayManager> gManager;

		Player aiPlayer;
		Player humanPlayer;

		/*
		 * Ray Picking variables
		 */

		glm::vec3 mousePointerRay{};
		float intDistance = 0;
		float minIntDistance = INT_MAX;
		glm::vec3 rayStart;

		/* UI Toggles */
		bool buildingSelected = false;
		Building * sBuilding = nullptr;	// Selected Building Pointer

		bool workerSelected = false;
		Unit * wSelected = nullptr;


	public:

		explicit GameScene(std::shared_ptr<vermin::Window> _window);
		~GameScene() = default;

		void InitEntities() override;

		void OnUpdate(float _deltaTime, float _totalTime) override;

		void OnRender() override;

		void OnImguiRender() override;

		void RunScene() override;

		void HandleInputs(float _deltaTime);

		template <class T>
		void CheckIfPicked(std::vector<std::shared_ptr<T>> _entities);

		void RayPicking();

		/* Game Functions */
		bool AddUnit(UnitType _type, Player& _player);

	};

}
