//
// Created by skk7174 on 11/10/2018.
//
#pragma once

#include "../Engine/library.h"
#include "GameScene.h"

namespace v_game {

	class Game
	{

		std::shared_ptr<vermin::Window> window;

		bool exitGame = false;

		std::unique_ptr<v_game::GameScene> currentScene;

	public:

		Game();
		~Game();

		void Init();

		void Run();

		void CleanUp();

	private:

	};

}
