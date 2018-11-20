//
// Created by skk7174 on 11/10/2018.
//
#pragma once

#include "library.h"
#include "GameScene.h"
#include "MenuScene.h"

namespace v_game {

	class Game
	{

		std::shared_ptr<vermin::Window> window;

		bool exitGame = false;

		std::unique_ptr<v_game::GameScene> currentScene;
		std::unique_ptr<v_game::MenuScene> menuScene;

		vermin::ImGuiLog imguiLogger;

	public:

		Game();
		~Game();

		void Init();

		void Run();

		void CleanUp();

	private:

	};

}
