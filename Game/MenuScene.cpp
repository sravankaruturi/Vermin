#include "MenuScene.h"

namespace v_game{

	MenuScene::MenuScene(std::shared_ptr<vermin::Window> _window)
		: Scene(_window)
	{

		deltaTime = glfwGetTime() - 0.0f;
		totalTime = glfwGetTime();

	}

	void MenuScene::OnImguiRender(){

		ImGui::Begin("##Menu");

		if ( ImGui::Button("Start Game") ){
			startGame = true;
		}

		if ( ImGui::Button("Quit") ){
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

	}

	void MenuScene::InitEntities(){

	}

	void MenuScene::HandleInputs(float _deltaTime) {
		Scene::HandleInputs();
	}

	void MenuScene::OnRender(){

	}

}
