//
// Created by Sravan Karuturi on 11/11/2018.
//

#ifndef GAME_GAMEPLAYMANAGER_H
#define GAME_GAMEPLAYMANAGER_H

#include "Player.h"
#include <memory>

namespace v_game
{
	
	class GamePlayManager {

	private:

		std::unique_ptr<Player> humanPlayer;
		std::unique_ptr<Player> aiPlayer;

		vermin::Terrain * gameTerrain;

	public:

		vermin::Terrain* GameTerrain() const
		{
			return gameTerrain;
		}

		void SetGameTerrain(vermin::Terrain* _gameTerrain)
		{
			gameTerrain = _gameTerrain;
		}

		static const int max_population = 20;


		GamePlayManager();

		~GamePlayManager() = default;

		void StartGame();

		void UpdateGame(float _deltaTime, float _totalTime);

		void Render();

		void HandleInputs();

		void CleanUp();

		void LoadAssets();

	};

}

#endif //GAME_GAMEPLAYMANAGER_H