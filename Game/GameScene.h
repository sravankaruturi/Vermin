#pragma once

#include "../Engine/library.h"
#include "../Engine/Terrain.h"
#include "glm/detail/type_mat.hpp"

namespace v_game {

	class GameScene : public vermin::Scene{

	private:

		/* Camera Constraints */
		glm::vec4 camConstraints{-2.f, 22.f, 2.f, 26.f};

		std::shared_ptr<vermin::Terrain> gameTerrain;

		vermin::Grid grid;
		glm::mat4 projectionMatrix;

	public:

		GameScene(std::shared_ptr<vermin::Window> _window);
		~GameScene() = default;

		void InitEntities() override;

		void OnUpdate(float _deltaTime, float _totalTime) override;

		void OnRender() override;

		void OnImguiRender() override;

		void RunScene() override;

		void HandleInputs(float _deltaTime);

	};

}