#include "GameScene.h"
#include <glm/gtc/matrix_transform.inl>

namespace v_game {



	void GameScene::OnRender()
	{

		// TODO: This can actually be a constant variable since we are going for full screen.
		const auto persp_projection_matrix = glm::perspective(45.0f, float(window->GetWidth()) / window->GetHeight(), 0.1f, 100.0f);

		glm::mat4 projection_matrices[4] = { persp_projection_matrix };
		glm::mat4 view_matrices[4] = { this->activeCamera->GetViewMatrix() };

		for (auto it : ASMGR.shaders)
		{
			it.second->use();

			if (it.first != "terrain" && it.first != "axes" && it.first != "bob_lamp")
			{
				it.second->setMat4("u_ViewMatrix", this->activeCamera->GetViewMatrix());
				it.second->setMat4("u_ProjectionMatrix", persp_projection_matrix);
			}

		}

		{
			std::vector<std::string> multiple_viewport_shaders = {
				"axes",
				"bob_lamp",
				"terrain"
			};

			for (auto& it : multiple_viewport_shaders) {

				auto shader_pointer = ASMGR.shaders.at(it);
				shader_pointer->use();
				auto loc = shader_pointer->GetUniformLocation("u_ViewMatrix");
				PE_GL(glUniformMatrix4fv(loc, 4, GL_FALSE, &view_matrices[0][0][0]));

				loc = shader_pointer->GetUniformLocation("u_ProjectionMatrix");
				PE_GL(glUniformMatrix4fv(loc, 4, GL_FALSE, glm::value_ptr(projection_matrices[0])));

			}
		}

		for (const auto& it : entities) {
			it->Render();
		}

		for (const auto& it : animatedEntities) {
			it->Render();
		}


		gameTerrain->Render();
		grid.Render();

		gManager->Render();

	}

	void GameScene::OnImguiRender()
	{

		ImGui::Begin("Camera Constraint");

		float distance = glm::distance(activeCamera->GetPosition(), gameTerrain->GetPosition());

		ImGui::Text("The Distance between the Camera Position and the Terrain Position , %f", distance);

		ImGui::End();

	}

	void GameScene::RunScene()
	{

		while (!shutDown)
		{

			deltaTime = glfwGetTime() - totalTime;
			totalTime = glfwGetTime();

			this->HandleInputs(deltaTime);

			PE_GL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
			PE_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			PE_GL(glViewport(0, 0, window->GetWidth(), window->GetHeight()));

			this->OnUpdate(deltaTime, totalTime);

			this->OnRender();

#if ENABLE_GUI
			// GUI Render
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();;

			this->OnImguiRender();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

			window->Update(deltaTime);

		}

	}

	void GameScene::HandleInputs(float _deltaTime)
	{

		Scene::HandleInputs();

		if (window->IsKeyPressedOrHeld(GLFW_KEY_W))
		{
			activeCamera->ProcessIsoMetricMovement(vermin::Camera::forward, _deltaTime);
			activeCamera->Clamp(camConstraints);
		}

		if (window->IsKeyPressedOrHeld(GLFW_KEY_S))
		{
			activeCamera->ProcessIsoMetricMovement(vermin::Camera::back, _deltaTime);
			activeCamera->Clamp(camConstraints);
		}

		if (window->IsKeyPressedOrHeld(GLFW_KEY_A))
		{
			activeCamera->ProcessIsoMetricMovement(vermin::Camera::leftside, _deltaTime);
			activeCamera->Clamp(camConstraints);
		}

		if (window->IsKeyPressedOrHeld(GLFW_KEY_D))
		{
			activeCamera->ProcessIsoMetricMovement(vermin::Camera::rightside, _deltaTime);
			activeCamera->Clamp(camConstraints);
		}

		if (window->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			activeCamera->ProcessMouseMovement(window->mouseOffsetX, 0);
		}

	}

	GameScene::GameScene(std::shared_ptr<vermin::Window> _window)
		: Scene(_window)
	{

		grid.Init();

		gameTerrain = std::make_shared<vermin::Terrain>(25, 25, 0.5, 0.5, std::string(TEXTURE_FOLDER) + std::string("heightmap.jpg"));
		LOGGER.AddToLog("Terrain Loaded...");

		gManager = std::make_unique<GamePlayManager>();
		gManager->SetGameTerrain(gameTerrain.get());

	}

	void GameScene::InitEntities()
	{

		LOGGER.AddToLog("Initializing Entities...");

		cameras.emplace("First", std::make_shared<vermin::Camera>("First", glm::vec3(0, 5, 10), glm::vec3(0.5, -0.5, -0.5), glm::vec3(0, 1, 0)));
		ActivateCamera(cameras.at("First"));

		LOGGER.AddToLog("Cameras Initialized...");

		gManager->StartGame();

	}

	void GameScene::OnUpdate(float _deltaTime, float _totalTime)
	{

		gameTerrain->ClearColours();

		projectionMatrix = glm::perspective(45.0f, float(window->GetWidth()) / window->GetHeight(), 0.1f, 100.0f);



		gameTerrain->Update(_deltaTime, _totalTime);

		grid.Update(activeCamera->GetViewMatrix(), projectionMatrix);

		gManager->UpdateGame(_deltaTime, _totalTime);

	}

}