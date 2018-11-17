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
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), false);
		ImGui_ImplOpenGL3_Init();

		// Setup style
		ImGui::StyleColorsDark();

		LOGGER.SetImGuiLogger(&imguiLogger);
#endif

		menuScene = std::make_unique<v_game::MenuScene>(window);
		currentScene = std::make_unique<v_game::GameScene>(window);

	}

	Game::~Game() {

	}

	void Game::Init()
	{

		// currentScene->InitEntities();

	}

	void Game::Run()
	{

		while ( !menuScene->StartGame() ){
			menuScene->RunScene();
		}

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
