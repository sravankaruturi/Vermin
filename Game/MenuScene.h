#pragma once

#include "../Engine/library.h"
#include "glm/detail/type_mat.hpp"

namespace v_game{

	class MenuScene : public vermin::Scene{

	private:

		bool startGame = false;
		bool quitGame = false;

	public:
		explicit MenuScene(std::shared_ptr<vermin::Window> _window);

		void InitEntities() override;

		void OnRender() override;

		void OnImguiRender() override;

		void RunScene() override;

		void HandleInputs(float _deltaTime);

		bool StartGame();

		bool QuitGame();

	};

}
