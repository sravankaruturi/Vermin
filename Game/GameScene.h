#pragma once

#include "../Engine/library.h"
#include "../Engine/Configurations.h"
#include "../Engine/FolderLocations.h"
#include "../Engine/Terrain.h"

namespace v_game {

	class GameScene : public vermin::Scene{

	public:

		GameScene(std::shared_ptr<vermin::Window> _window);
		~GameScene() = default;

		std::shared_ptr<vermin::Terrain> gameTerrain;

		void InitEntities() override;

		void OnUpdate(float _deltaTime, float _totalTime) override;

		void OnRender() override;

		void OnImguiRender() override;

		void RunScene() override;

		void HandleInputs();

	};

}