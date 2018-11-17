#include "MenuScene.h"

namespace v_game{

	MenuScene::MenuScene(std::shared_ptr<vermin::Window> _window)
		: Scene(_window)
	{

		deltaTime = glfwGetTime() - 0.0f;
		totalTime = glfwGetTime();

	}

	void MenuScene::OnImguiRender(){

		ImVec2 windowPos = ImVec2(window->GetWidth() / 4, window->GetHeight() / 4);

		ImVec2 windowSize = ImVec2(window->GetWidth() / 2, window->GetHeight() / 2);

		ImGui::SetNextWindowBgAlpha(0.0f);
		ImGui::SetNextWindowPos(windowPos);
		ImGui::SetNextWindowSize(windowSize);
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoScrollbar
			| ImGuiWindowFlags_NoSavedSettings
			;

		ImGuiIO& io = ImGui::GetIO();
		io.FontGlobalScale = 3.0f;

		ImGui::Begin("##Menu", NULL, flags);

		ImVec2 buttonSize = ImVec2(windowSize.x * 0.96f, windowSize.y * 0.47f);

		if ( ImGui::Button("Start Game", buttonSize ) ){
			startGame = true;
		}

		if ( ImGui::Button("Quit", buttonSize) ){
			quitGame = true;
		}

		ImGui::End();

	}

	bool MenuScene::StartGame(){
		return startGame;
	}

	bool MenuScene::QuitGame(){
		return quitGame;
	}

	void MenuScene::RunScene(){
		
		while( !shutDown && !startGame && !quitGame){

			deltaTime = glfwGetTime() - totalTime;
			totalTime = glfwGetTime();

			this->HandleInputs(deltaTime);

			// TODO: This entire block is re-written in both the scenes. That is not ideal. Fix it
			PE_GL(glClearColor(0.2f, 0.1f, 0.2f, 1.0f));
			PE_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			PE_GL(glViewport(0, 0, window->GetWidth(), window->GetHeight()));

#if ENABLE_GUI
			// GUI Render
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();;

			ImGui::NewFrame();

#endif
			this->OnUpdate(deltaTime, totalTime);

			this->OnRender();

#if ENABLE_GUI
			this->OnImguiRender();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

			window->Update(deltaTime);

		}

#if ENABLE_GUI
		ImGuiIO& io = ImGui::GetIO();
		io.FontGlobalScale = 1.0f;
#endif

	}

	void MenuScene::InitEntities(){

	}

	void MenuScene::HandleInputs(float _deltaTime) {
		Scene::HandleInputs();
	}

	void MenuScene::OnRender(){

	}

}
