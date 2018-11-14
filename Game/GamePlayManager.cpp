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

		LoadAssets();

	}

	void GamePlayManager::UpdateGame(float _deltaTime, float _totalTime)
	{

	}

	void GamePlayManager::Render()
	{


	}

	void GamePlayManager::CleanUp()
	{



	}

	void GamePlayManager::LoadAssets()
	{

		std::shared_ptr<vermin::Texture> building_diffuse = std::make_shared<vermin::Texture>(
				MODEL_FOLDER + std::string("Medieval_House/Medieval_House_Diff.png"), false
				);
		ASMGR.AddToTextures("building_diffuse", building_diffuse);

		std::shared_ptr<vermin::Texture> knight_diffuse = std::make_shared<vermin::Texture>(
				MODEL_FOLDER + std::string("RTSDemo/Materials/DemoTexture.png"), false
				);
		ASMGR.AddToTextures("knight_demo", knight_diffuse);

		std::shared_ptr<vermin::Object> building_obj = std::make_shared<vermin::Object>(
				MODEL_FOLDER + std::string("Medieval_House/Medieval_House.obj")
				);
		ASMGR.AddToObjects("Medieval_House", building_obj);
		ASMGR.objects.at("Medieval_House")->GetMeshes()[0]->textureNames.emplace_back("building_diffuse");

		std::shared_ptr<vermin::Object> knightWalkAnimation = std::make_shared<vermin::Object>(
				MODEL_FOLDER + std::string("RTSDemo/Walking.fbx")
				);
		knightWalkAnimation->GetMeshes()[0]->textureNames[0] = ("knight_demo");
		ASMGR.AddToObjects("Walking", knightWalkAnimation);

		std::shared_ptr<vermin::Object> knightDyingAnimation = std::make_shared<vermin::Object>(
				MODEL_FOLDER + std::string("RTSDemo/Dying.fbx")
				);
		knightDyingAnimation->GetMeshes()[0]->textureNames[0] = ("knight_demo");
		ASMGR.AddToObjects("Dying", knightDyingAnimation);

		std::shared_ptr<vermin::Object> knightIdleAnimation = std::make_shared<vermin::Object>(
				MODEL_FOLDER + std::string("RTSDemo/HappyIdle.fbx")
				);
		knightIdleAnimation->GetMeshes()[0]->textureNames[0] = ("knight_demo");
		ASMGR.AddToObjects("HappyIdle", knightIdleAnimation);

		std::shared_ptr<vermin::Object> knightSwordAnimation = std::make_shared<vermin::Object>(
				MODEL_FOLDER + std::string("RTSDemo/SwordAndShieldSlash.fbx")
				);
		knightSwordAnimation->GetMeshes()[0]->textureNames[0] = ("knight_demo");
		ASMGR.AddToObjects("SwordAndShieldSlash", knightSwordAnimation);

	}
}
