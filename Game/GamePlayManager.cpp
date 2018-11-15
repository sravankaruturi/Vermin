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
				MODEL_FOLDER + std::string("RTSDemo/Knight_Walking.fbx")
				);
		knightWalkAnimation->GetMeshes()[0]->textureNames[0] = ("knight_demo");
		ASMGR.AddToObjects("Knight_Walking", knightWalkAnimation);

		std::shared_ptr<vermin::Object> knightDyingAnimation = std::make_shared<vermin::Object>(
				MODEL_FOLDER + std::string("RTSDemo/Knight_Dying.fbx")
				);
		knightDyingAnimation->GetMeshes()[0]->textureNames[0] = ("knight_demo");
		ASMGR.AddToObjects("Knight_Dying", knightDyingAnimation);

		std::shared_ptr<vermin::Object> knightIdleAnimation = std::make_shared<vermin::Object>(
				MODEL_FOLDER + std::string("RTSDemo/Knight_Happy_Idle.fbx")
				);
		if (knightIdleAnimation->GetMeshes().size() > 0) {
			knightIdleAnimation->GetMeshes()[0]->textureNames[0] = ("knight_demo");
			ASMGR.AddToObjects("Knight_Happy_Idle", knightIdleAnimation);
		}

		std::shared_ptr<vermin::Object> knightSwordAnimation = std::make_shared<vermin::Object>(
				MODEL_FOLDER + std::string("RTSDemo/SwordAndShieldSlash.fbx")
				);
		knightSwordAnimation->GetMeshes()[0]->textureNames[0] = ("knight_demo");
		ASMGR.AddToObjects("SwordAndShieldSlash", knightSwordAnimation);

		std::shared_ptr<vermin::Texture> allBaseUnits = std::make_shared<vermin::Texture>(
			MODEL_FOLDER + std::string("Villager/WK_Standard_Units.tga"), false
			);
		ASMGR.AddToTextures("base_units", allBaseUnits);

		std::shared_ptr<vermin::Object> villagerBase = std::make_shared<vermin::Object>(
			MODEL_FOLDER + std::string("Villager/Worker_Happy_Idle.fbx")
			);
		villagerBase->GetMeshes()[0]->textureNames[0] = ("base_units");
		ASMGR.AddToObjects("Worker_Happy_Idle", villagerBase);

		std::shared_ptr<vermin::Object> workerWalking = std::make_shared<vermin::Object>(
			MODEL_FOLDER + std::string("Villager/Worker_Walking.fbx")
			);
		workerWalking->GetMeshes()[0]->textureNames[0] = ("base_units");
		ASMGR.AddToObjects("Worker_Walking", workerWalking);

		std::shared_ptr<vermin::Object> workerDying = std::make_shared<vermin::Object>(
			MODEL_FOLDER + std::string("Villager/Worker_Dying.fbx")
			);
		workerDying->GetMeshes()[0]->textureNames[0] = ("base_units");
		ASMGR.AddToObjects("Worker_Dying", workerDying);

	}
}
