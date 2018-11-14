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

		ASMGR.shaders.at("unit")->use();
		ASMGR.shaders.at("unit")->setVec4("u_PlayerColour", humanPlayer.pColour);
		for (const auto& it : humanPlayer.units) {
			it->Render();
		}

		ASMGR.shaders.at("town_center")->use();
		ASMGR.shaders.at("town_center")->setVec4("u_PlayerColour", humanPlayer.pColour);
		for (const auto& it : humanPlayer.buildings) {
			it->Render();
		}

		ASMGR.shaders.at("unit")->use();
		ASMGR.shaders.at("unit")->setVec4("u_PlayerColour", aiPlayer.pColour);
		for (const auto& it : aiPlayer.units) {
			it->Render();
		}

		ASMGR.shaders.at("town_center")->use();
		ASMGR.shaders.at("town_center")->setVec4("u_PlayerColour", aiPlayer.pColour);
		for (const auto& it : aiPlayer.buildings) {
			it->Render();
		}


		gameTerrain->Render();
		grid.Render();

		gManager->Render();

	}

	void GameScene::OnImguiRender()
	{

		ImGui::NewFrame();

		if ( ImGui::BeginMainMenuBar()){
			if ( ImGui::BeginMenu("Windows")){
				if ( ImGui::MenuItem("Log") ){
					displayLogWindow = true;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		if ( displayLogWindow ){
			LOGGER.Render(&displayLogWindow);
		}

		{
			ImGui::Begin("Test");
			ImGui::Text("DeltaTime: %lf", deltaTime);
			ImGui::Text("TotalTime: %lf", totalTime);
			ImGui::End();
		}

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

		deltaTime = glfwGetTime() - 0.0f;
		totalTime = glfwGetTime();

		grid.Init();

		gameTerrain = std::make_shared<vermin::Terrain>(
			25, 25, 0.5, 0.5, std::string(TEXTURE_FOLDER) + std::string("heightmap.jpg")
			);
		LOGGER.AddToLog("Terrain Loaded...");

		gManager = std::make_unique<GamePlayManager>();
		gManager->SetGameTerrain(gameTerrain.get());

		// Call this before initializing Players to load the Entities here.
		InitEntities();

		const float y1 = gameTerrain->GetHeightAtPos(2, 2);
		const float y2 = gameTerrain->GetHeightAtPos(22, 22);

		// TODO: Fill the values properly.
		humanPlayer = { glm::vec3(2, y1, 2), PlayerType::Human };
		aiPlayer = { glm::vec3(22, y2, 22), PlayerType::Ai };

	};

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

		this->RayPicking();

		for ( const auto& it: humanPlayer.buildings ){
			it->Update(_deltaTime);
		}

		for ( const auto& it: humanPlayer.units ){

			it->Update(_deltaTime, gameTerrain.get());
			it->PlayAnimation(_deltaTime, _totalTime);
			
		}

		for (const auto& it : aiPlayer.buildings) {
			it->Update(_deltaTime);
		}

		for (const auto& it : aiPlayer.units) {

			it->Update(_deltaTime, gameTerrain.get());
			it->PlayAnimation(_deltaTime, _totalTime);

		}

	}

	template <class T>
	void GameScene::CheckIfPicked(std::vector<std::shared_ptr<T>> _entities){

		for (auto& it : _entities)
		{
			// We cast all the Units to Entity*
			auto entIt = (vermin::Entity*)(it.get());

			if ((window->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) && (entIt->CheckIfMouseOvered(rayStart, mousePointerRay, minIntDistance)))
			{
				if (intDistance < minIntDistance)
				{
					minIntDistance = intDistance;
					if (!window->IsKeyPressedOrHeld(GLFW_KEY_LEFT_SHIFT)) {
						selectedEntities.clear();
					}
					if (std::find(selectedEntities.begin(), selectedEntities.end(), entIt) == selectedEntities.end()) {
						selectedEntities.push_back(entIt);
					}
				}
			}
			entIt->SetSelectedInScene(false);
		}
	}


	void GameScene::RayPicking() {

		rayStart = this->activeCamera->GetPosition();
		mousePointerRay = activeCamera->GetMouseRayDirection(window->mouseX, window->mouseY, window->GetWidth(), window->GetHeight(), projectionMatrix);

		if (nullptr != activeCamera)
		{
			vermin::Ray mouse_pointer_ray_ray{ activeCamera->GetPosition(), mousePointerRay };
			gameTerrain->GetMouseRayPoint(mouse_pointer_ray_ray);
		}

		const glm::ivec2 target_node = gameTerrain->pointedNodeIndices;

		this->CheckIfPicked<vermin::Entity>(entities);
		this->CheckIfPicked<vermin::AnimatedEntity>(animatedEntities);
		this->CheckIfPicked<Building>(humanPlayer.buildings);
		this->CheckIfPicked<Unit>(humanPlayer.units);
		this->CheckIfPicked<Building>(aiPlayer.buildings);
		this->CheckIfPicked<Unit>(aiPlayer.units);

		for ( auto it: selectedEntities){
			it->SetSelectedInScene(true);
		}

		if ( window->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
		{
			
			const int number_of_selected_entities = selectedEntities.size();
			const int number_of_rows = glm::ceil(glm::sqrt(number_of_selected_entities));
			const int number_of_columns = glm::ceil((float)number_of_selected_entities / number_of_rows);
			int entity_counter = 0;

			for (int row_counter = 0; row_counter < number_of_rows; row_counter++) {
				for (int column_counter = 0; column_counter < number_of_columns; column_counter++) {

					if (entity_counter >= number_of_selected_entities) {
						break;
					}

					glm::ivec2 temp_target_node = target_node;
					temp_target_node.x += (row_counter - number_of_rows / 2);
					temp_target_node.y += (column_counter - number_of_rows / 2);
					selectedEntities[entity_counter++]->setTargetNode(temp_target_node);

				}
			}

		}

	}

}
