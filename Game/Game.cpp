//
// Created by skk7174 on 11/10/2018.
//

#include "Game.h"

namespace v_game {

	Game::Game() {

#if _DEBUG
		window = std::make_shared<vermin::Window>(800, 600, "The Game", false);
#else
		window = std::make_shared<vermin::Window>(1920, 1080, "The Game", false);
#endif

		

#if ENABLE_GUI
		ImGui::CreateContext();

		ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), false);
		ImGui_ImplOpenGL3_Init();

		// Setup style
		ImGui::StyleColorsDark();

		vermin::ImGuiLog imgui_logger;
		LOGGER.SetImGuiLogger(&imgui_logger);
#endif

		currentScene = std::make_unique<v_game::GameScene>(window);

	}

	Game::~Game() {

	}

	void Game::Init()
	{

		currentScene->InitEntities();

	}

	void Game::Run()
	{

		while (!currentScene->ShutDown()) {

			currentScene->RunScene();

		}

	}

	void Game::CleanUp()
	{

#if ENABLE_GUI

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

#endif

	}

}