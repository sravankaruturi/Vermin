//
// Created by Sravan Karuturi on 11/11/2018.
//

#include "GamePlayManager.h"
#include "AssetManager.h"

namespace v_game
{
	GamePlayManager::GamePlayManager()
	= default;

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


	// ModelPath, ModelName, TexturePath, TextureName
	void GamePlayManager::LoadModelAndAssociateWithTexture(
			const std::array<std::string, 4> _data
			) const
	{

		// We first Check if the Texture already exists
		const bool texture_load_check = ASMGR.IsTextureLoaded(_data[3]);
		if ( !texture_load_check ){
			ASMGR.AddToTextures(
					_data[3], 
					std::make_shared<vermin::Texture>(_data[2], false)
					);
		}


		std::shared_ptr<vermin::Object> temp_obj = std::make_shared<vermin::Object>(
				_data[0]
				);
		ASMGR.AddToObjects(_data[1], temp_obj);
		auto temp_vector = temp_obj->GetMeshes();
		if (!temp_vector[0]->textureNames.empty()){
			temp_vector[0]->textureNames[0] = _data[3];
		}else{
			temp_vector[0]->textureNames.emplace_back(_data[3]);
		}

	}

	void GamePlayManager::LoadAssets()
	{

		std::vector<std::array<std::string, 4>> mod_tex_array = {
			{
				MODEL_FOLDER + std::string("Medieval_House/Medieval_House.obj"),
				std::string("Medieval_House"),
				MODEL_FOLDER + std::string("Medieval_House/Medieval_House_Diff.png"),
				std::string("Medieval_House_Diff")
			},
			{
				MODEL_FOLDER + std::string("RTSDemo/Knight_Walking.fbx"),
				std::string("Knight_Walking"),
				MODEL_FOLDER + std::string("RTSDemo/Materials/DemoTexture.png"),
				std::string("Knight_Diffuse")
			},
			{
				MODEL_FOLDER + std::string("RTSDemo/Knight_Dying.fbx"),
				std::string("Knight_Dying"),
				MODEL_FOLDER + std::string("RTSDemo/Materials/DemoTexture.png"),
				std::string("Knight_Diffuse")
			},
			{
				MODEL_FOLDER + std::string("RTSDemo/Knight_Happy_Idle.fbx"),
				std::string("Knight_Happy_Idle"),
				MODEL_FOLDER + std::string("RTSDemo/Materials/DemoTexture.png"),
				std::string("Knight_Diffuse")
			},
			{
				MODEL_FOLDER + std::string("RTSDemo/Knight_Attack.fbx"),
				std::string("Knight_Attack"),
				MODEL_FOLDER + std::string("RTSDemo/Materials/DemoTexture.png"),
				std::string("Knight_Diffuse")
			}
		};

		for ( const auto& it: mod_tex_array ){
			this->LoadModelAndAssociateWithTexture(
					it
					);
		}

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

	void GamePlayManager::HandleInputs() {
		throw std::runtime_error("Function not implemented");
	}
}
