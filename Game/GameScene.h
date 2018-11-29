#pragma once

#include "library.h"
#include "Terrain.h"
#include "glm/detail/type_mat.hpp"

#include "GamePlayManager.h"
#include "Building.h"
#include "Unit.h"
#include "Tree.h"

namespace v_game {

	enum class PlayerType
	{
		Human,
		Ai
	};

	enum class PlayerMode
	{
		Placing,
		Playing
	};

	struct Player{

		unsigned int rWood = 0;
		unsigned int rStone = 0;

		PlayerType pType = PlayerType::Ai;
		PlayerMode pMode = PlayerMode::Playing;

		glm::vec4 pColour{0 ,0, 1, 0.3};

		std::vector<std::shared_ptr<Building>> buildings{};
		std::vector<std::shared_ptr<Unit>> units{};

		glm::vec3 baseStartPosition{0};

		Player() = default;

		Player(glm::vec3 _baseStartPosition, PlayerType _pType){

			baseStartPosition = _baseStartPosition;

			pType = _pType;

			// Let us give some wood and stone to the Player.
			rWood = 1200;
			rStone = 1200;

			pColour = (pType == PlayerType::Human) ? glm::vec4(1, 0, 0, 0.3) : glm::vec4(0, 0, 1, 0.3);

		}

	};

	class GameScene : public vermin::Scene{

	private:

		/* GUI Variables for the HUD */
		const float distanceFromEdges = 10.0f;

		ImGuiWindowFlags resWinFlags =
				ImGuiWindowFlags_NoCollapse
				| ImGuiWindowFlags_NoInputs
				| ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoSavedSettings
				| ImGuiWindowFlags_NoTitleBar;

		ImVec2 resWinSize = ImVec2(200, 60);

		int resWinCorner = 1;

		/* GUI Variables */

		// Player Character Controls
		int pccCorner = 3;
		ImVec2 pccSize = ImVec2(300, 400);

		ImGuiWindowFlags pccFlags =
				ImGuiWindowFlags_NoCollapse
				| ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoSavedSettings;

		bool displayLogWindow = false;

		// Selection Window variables.
		ImGuiWindowFlags swFlags =
			ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_NoTitleBar
		;

		ImVec2 swSize = ImVec2(300, 200);

		/* UI Toggles */
		bool buildingSelected = false;
		Building * sBuilding = nullptr;	// Selected Building Pointer

		bool enemyUnitSelected = false;
		bool workerSelected = false;
		Unit * sWorker = nullptr;


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

		/* Temporary Entities */
		std::vector<std::unique_ptr<Building>> buildingPlacers;

		// There can only be one entity hovered over at a time.
		vermin::Entity * hoveredEntity;

		std::vector<std::unique_ptr<Tree>> trees;


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

		template <class T>
		void CheckIfHovered(std::vector<std::shared_ptr<T>> _entities);

		void RayPicking();

		/* Game Functions */
		bool AddUnit(UnitType _type, Player& _player);

		bool KillUnit(vermin::Entity * _entity);

		bool AddBuilding(BuildingType _type, Player& _player, const glm::vec3& _position) const;

		void SetTerrainObstacleForBuilding(const glm::ivec2& _buildingPosition ) const;

		vermin::Entity * GetEntityAtNodeIndex(const glm::ivec2& _nodeIndices);

	};

}
