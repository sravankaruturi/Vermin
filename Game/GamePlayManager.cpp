//
// Created by Sravan Karuturi on 11/11/2018.
//

#include "GamePlayManager.h"
#include "../Engine/Terrain.h"
#include "FolderLocations.h"
#include "AssetManager.h"

namespace v_game
{
	GamePlayManager::GamePlayManager()
	{
		
	}

	void GamePlayManager::StartGame()
	{

		const float y1 = gameTerrain->GetHeightAtPos(2, 2);
		const float y2 = gameTerrain->GetHeightAtPos(22, 22);


		std::shared_ptr<vermin::Texture> building_diffuse = std::make_shared<vermin::Texture>(MODEL_FOLDER + std::string("Medieval_House/Medieval_House_Diff.png"), false);
		ASMGR.AddToTextures("building_diffuse", building_diffuse);

		// Create the Player Objects.
		humanPlayer = std::make_unique<Player>(glm::vec3(2, y1, 2), PlayerType::Human);
		aiPlayer = std::make_unique<Player>(glm::vec3(22, y2, 22), PlayerType::Ai);

		ASMGR.objects.at("Medieval_House")->GetMeshes()[0]->textureNames.emplace_back("building_diffuse");

	}

	void GamePlayManager::UpdateGame(float _deltaTime, float _totalTime)
	{

		this->humanPlayer->Update(_deltaTime, _totalTime);
		this->aiPlayer->Update(_deltaTime, _totalTime);

	}

	void GamePlayManager::Render()
	{

		this->humanPlayer->Render();
		this->aiPlayer->Render();

	}

	void GamePlayManager::CleanUp()
	{



	}
}
