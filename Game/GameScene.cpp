#include "GameScene.h"
#include <glm/gtc/matrix_transform.inl>
#include <imgui_internal.h>

#define		NO_CAMERA_CONSTRAINTS	1

namespace v_game {

	void DrawHealthBars(float _perc)
	{

		ImVec2 size_arg = ImVec2(-1, 0);
		const char * overlay = "Health";
		ImVec4 bar_colour = ImVec4();

		if (_perc < 0.25)
		{
			bar_colour = ImVec4(0.90, 0.2, 0.2, 1.0);
		}
		else if (_perc > 0.75)
		{
			bar_colour = ImVec4(0.2, 0.90, 0.2, 1.0);
		}
		else
		{
			bar_colour = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		}

		//ImGui::ProgressBar(_perc, ImVec2(-1, 0), "Health");

		ImGuiWindow *window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiContext &g = *GImGui;
		const ImGuiStyle &style = g.Style;

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), g.FontSize + style.FramePadding.y * 2.0f);
		ImVec2 other_pos = ImVec2(pos.x + size.x, pos.y + size.y);
		ImRect bb(
			pos,
			other_pos
		);
		ImGui::ItemSize(bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, 0))
			return;

		// Render
		_perc = ImSaturate(_perc);
		ImGui::RenderFrame(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);
		bb.Expand(ImVec2(-style.FrameBorderSize, -style.FrameBorderSize));
		const ImVec2 fill_br = ImVec2(ImLerp(bb.Min.x, bb.Max.x, _perc), bb.Max.y);
		ImGui::RenderRectFilledRangeH(window->DrawList, bb, ImGui::ColorConvertFloat4ToU32(bar_colour), 0.0f, _perc,
			style.FrameRounding);

		// Default displaying the fraction as percentage string, but user can override it
		char overlay_buf[32];
		if (!overlay) {
			ImFormatString(overlay_buf, IM_ARRAYSIZE(overlay_buf), "%.0f%%", _perc * 100 + 0.01f);
			overlay = overlay_buf;
		}

		ImVec2 overlay_size = ImGui::CalcTextSize(overlay, NULL);
		if (overlay_size.x > 0.0f)
			ImGui::RenderTextClipped(ImVec2(ImClamp(fill_br.x + style.ItemSpacing.x, bb.Min.x,
				bb.Max.x - overlay_size.x - style.ItemInnerSpacing.x), bb.Min.y), bb.Max,
				overlay, NULL, &overlay_size, ImVec2(0.0f, 0.5f), &bb);

	}

	void GameScene::OnRender()
	{

		int test = '0';
		// TODO: This can actually be a constant variable since we are going for full screen.
		this->projectionMatrix = glm::perspective(45.0f, float(window->GetWidth()) / window->GetHeight(), 0.1f, 100.0f);

		glm::mat4 projection_matrices[4] = { projectionMatrix };
		glm::mat4 view_matrices[4] = { this->activeCamera->GetViewMatrix() };

		for (auto it : ASMGR.shaders)
		{
			it.second->use();

			if (it.first != "terrain" && it.first != "axes" && it.first != "bob_lamp")
			{
				it.second->setMat4("u_ViewMatrix", this->activeCamera->GetViewMatrix());
				it.second->setMat4("u_ProjectionMatrix", projectionMatrix);
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
		// grid.Render();

		gManager->Render();

	}

	void GameScene::OnImguiRender()
	{

#if _DEBUG
		if ( ImGui::BeginMainMenuBar()){
			if ( ImGui::BeginMenu("Windows")){
				if ( ImGui::MenuItem("Log") ){
					displayLogWindow = true;
				}
				ImGui::EndMenu();
			}

			ImGui::VerticalSeparator();

			ImGui::Text("DeltaTime: %lf", deltaTime);
			ImGui::Text("TotalTime: %lf", totalTime);

			ImGui::EndMainMenuBar();
		}
#endif

		ImVec2 window_pos = ImVec2(
				(resWinCorner & 1) ? ImGui::GetIO().DisplaySize.x - distanceFromEdges : distanceFromEdges,
				(resWinCorner & 2) ? ImGui::GetIO().DisplaySize.y - distanceFromEdges : distanceFromEdges);
		ImVec2 window_pos_pivot = ImVec2((resWinCorner & 1) ? 1.0f : 0.0f, (resWinCorner & 2) ? 1.0f : 0.0f);
		if (resWinCorner != -1)
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background


		ImGui::Begin("Resources", nullptr, resWinSize, 0.4f, resWinFlags | ImGuiWindowFlags_NoTitleBar);
		ImGui::LabelText("Wood", "%d", humanPlayer.rWood);
		ImGui::LabelText("Stone", "%d", humanPlayer.rStone);
		ImGui::End();

		window_pos = ImVec2((pccCorner & 1) ? ImGui::GetIO().DisplaySize.x - distanceFromEdges : distanceFromEdges,
							(pccCorner & 2) ? ImGui::GetIO().DisplaySize.y - distanceFromEdges : distanceFromEdges);
		window_pos_pivot = ImVec2((pccCorner & 1) ? 1.0f : 0.0f, (pccCorner & 2) ? 1.0f : 0.0f);
		if (pccCorner != -1)
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		ImGui::SetNextWindowBgAlpha(0.8f); // Transparent background
		ImGui::SetNextWindowSize(pccSize);


		ImGui::Begin("Your Units", nullptr, pccFlags);
		{

			for (auto &it: humanPlayer.buildings) {
				ImGui::Text("%s", it->GetEntityName().c_str());
			}

			ImGui::Separator();

			for (auto &it: humanPlayer.units) {
				ImGui::Text("%s", it->GetEntityName().c_str());
			}

		}

		ImGui::End();

		if ( displayLogWindow ){
			LOGGER.Render(&displayLogWindow);
		}

		// If Anthing Selected? Show that window.

		// IF One of the Buildings is selected.
		if (buildingSelected) {
			
			window_pos.y = ImGui::GetIO().DisplaySize.y - distanceFromEdges;
			window_pos.x = ImGui::GetIO().DisplaySize.x / 2;

			window_pos_pivot.y = 1;
			window_pos_pivot.x = 0.5;

			ImGui::SetNextWindowSize(swSize);
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

			ImGui::Begin("Town Center", nullptr, swFlags);

			DrawHealthBars(sBuilding->GetCurrentHPPerc());

			ImGui::Separator();

			if (ImGui::ImageButton((ImTextureID)ASMGR.textures.at("WorkerFace")->GetTextureId(), ImVec2(50, 50))) {
				this->AddUnit(UnitType::villager, humanPlayer);
			}

			ImGui::SameLine();

			if (ImGui::ImageButton((ImTextureID)ASMGR.textures.at("KnightFace")->GetTextureId(), ImVec2(50, 50))) {
				this->AddUnit(UnitType::warrior, humanPlayer);
			}

			ImGui::End();

		}else if (workerSelected)
		{
			window_pos.y = ImGui::GetIO().DisplaySize.y - distanceFromEdges;
			window_pos.x = ImGui::GetIO().DisplaySize.x / 2;

			window_pos_pivot.y = 1;
			window_pos_pivot.x = 0.5;

			ImGui::SetNextWindowSize(swSize);
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

			ImGui::Begin("Worker", nullptr, swFlags);

			ImGui::Image((ImTextureID)sWorker->FaceTextureId(), ImVec2(50, 50));

			DrawHealthBars(sWorker->GetCurrentHPPerc());

			ImGui::Separator();

			ImGui::End();

		}



		
		
		ImGui::ShowDemoWindow();

	}

	void GameScene::RunScene()
	{

#if __APPLE__
		window->UpdateFrameSize();
#endif
		while (!shutDown)
		{

			deltaTime = glfwGetTime() - totalTime;
			totalTime = glfwGetTime();

			this->HandleInputs(deltaTime);

			PE_GL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
			PE_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			PE_GL(glViewport(0, 0, window->GetPixelWidth(), window->GetPixelHeight()));

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

	void GameScene::HandleInputs(float _deltaTime)
	{

		Scene::HandleInputs();

		if (window->IsKeyPressedOrHeld(GLFW_KEY_W))
		{
			
#if NO_CAMERA_CONSTRAINTS
			activeCamera->ProcessKeyboard(vermin::Camera::forward, _deltaTime);
#else
			activeCamera->ProcessIsoMetricMovement(vermin::Camera::forward, _deltaTime);
			activeCamera->Clamp(camConstraints);
#endif
		}

		if (window->IsKeyPressedOrHeld(GLFW_KEY_S))
		{
			
#if NO_CAMERA_CONSTRAINTS
			activeCamera->ProcessKeyboard(vermin::Camera::back, _deltaTime);
#else
			activeCamera->ProcessIsoMetricMovement(vermin::Camera::back, _deltaTime);
			activeCamera->Clamp(camConstraints);
#endif
		}

		if (window->IsKeyPressedOrHeld(GLFW_KEY_A))
		{
			
#if NO_CAMERA_CONSTRAINTS
			activeCamera->ProcessKeyboard(vermin::Camera::leftside, _deltaTime);
#else
			activeCamera->ProcessIsoMetricMovement(vermin::Camera::leftside, _deltaTime);
			activeCamera->Clamp(camConstraints);
#endif
		}

		if (window->IsKeyPressedOrHeld(GLFW_KEY_D))
		{
			
#if NO_CAMERA_CONSTRAINTS
			activeCamera->ProcessKeyboard(vermin::Camera::rightside, _deltaTime);
#else
			activeCamera->ProcessIsoMetricMovement(vermin::Camera::rightside, _deltaTime);
			activeCamera->Clamp(camConstraints);
#endif
		}

		if (window->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
#if NO_CAMERA_CONSTRAINTS
			activeCamera->ProcessMouseMovement(window->mouseOffsetX, window->mouseOffsetY);
#else
			activeCamera->ProcessMouseMovement(window->mouseOffsetX, 0);
#endif
		}

		if (window->IsKeyPressedAndReleased(GLFW_KEY_BACKSLASH)) {
			this->displayLogWindow = !this->displayLogWindow;
		}

	}

	GameScene::GameScene(std::shared_ptr<vermin::Window> _window)
			: Scene(std::move(_window))
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

		for (auto& it : entities) {
			it->Update(_deltaTime);
		}

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


		/* Update Selection Flags */
		this->sBuilding = nullptr;
		this->buildingSelected = false;
		for ( const auto& it: humanPlayer.buildings){
			this->buildingSelected |= it->IsSelectedInScene();
			if ( it->IsSelectedInScene() ){
				this->sBuilding = it.get();
			}
		}

		this->sWorker = nullptr;
		this->workerSelected = false;
		for (const auto& it : humanPlayer.units) {
			this->workerSelected |= it->IsSelectedInScene();
			if (it->IsSelectedInScene()) {
				this->sWorker = it.get();
			}
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

	bool GameScene::AddUnit(UnitType _type, Player& _player){

		// We Get the Unit Cost
		int w_cost = required_wood[static_cast<int>(_type)];
		int s_cost = required_stone[static_cast<int>(_type)];

		if ( _player.rWood < w_cost || _player.rStone < s_cost ){
			LOGGER.AddToLog("Not Enough resources", vermin::PE_LOG_WARN);
			return false;
		}

		_player.rWood -= w_cost;
		_player.rStone -= s_cost;

		unsigned t_index = _player.units.size();

		_player.units.emplace_back(
				std::make_shared<Unit>(_type)
				);

		_player.units[t_index]->SetPosition(_player.villagerStartPosition);

		_player.villagerStartPosition.x += 1.5;
		_player.villagerStartPosition.z += 1.5;

		return true;

	}

}
