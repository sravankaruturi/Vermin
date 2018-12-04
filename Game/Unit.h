//
// Created by skk7174 on 11/12/2018.
//

#ifndef GAME_UNIT_H
#define GAME_UNIT_H
#include "AnimatedEntity.h"
#include "Terrain.h"
#include "gameDefinitions.h"


namespace v_game {

	class ResourceObject;

	enum class UnitType
	{

		villager,
		warrior,
		catapult

	};

	enum class AnimType
	{

		idle,
		walking,
		death,
		attack

	};

	enum class UnitState{
		walking,
		idle,
		gathering,
		attacking
	};

	const std::string animation_names[3][4] = {
		{
			"Worker_Happy_Idle",
			"Worker_Walking",
			"Worker_Dying",
			"Knight_Attack",
		},
		{
			"Knight_Happy_Idle",
			"Knight_Walking",
			"Knight_Dying",
			"Knight_Attack"
		},
		{
			"Catapult_Happy_Idle",
			"Catapult_Walking",
			"Catapult_Dying",
			"Catapult_Attack"
		}
	};

	const int required_wood_for_units[3] = {
		30, 30, 40
	};

	const int required_stone_for_units[3] = {
		30, 40, 40
	};

	class Unit : public vermin::AnimatedEntity {

		public:

			explicit Unit(UnitType _type, short _team);

			float GetCurrentHPPerc();

			~Unit() { entityType = 1; }

			void Update(float _deltaTime, vermin::Terrain * _terrain, Resources& _resources);

			float resourceTimer = 0.0f;
			float resourceTimeLimit = 2.0f;

			ResourceObject * resourceEntity = nullptr;
			ResourceType rType;

		protected:

			/* Pathing Stuff */
			std::vector<vermin::MapTile *> path;
			float totalTimeCounterForPathing = 0;
			float movementSpeed = 2.0f;

			std::string idleObjectName;
			std::string walkObjectName;
			std::string attackObjectName;
			std::string deathObjectName;

			unsigned int faceTextureID;

			UnitState currentState = UnitState::idle;

			UnitType type;


		public:
			UnitType Type() const
			{
				return type;
			}

			UnitState getCurrentState() const;

			void setCurrentState(UnitState currentState);

			unsigned FaceTextureId() const
			{
				return faceTextureID;
			}

			void SetFaceTextureId(unsigned _faceTextureId)
			{
				faceTextureID = _faceTextureId;
			}

			const static std::string ToString(UnitState _state){
				switch(_state){
					case UnitState::attacking:
						return "Attacking";
					case UnitState::idle:
						return "Idle";
					case UnitState::walking:
						return "Walking";
					case UnitState::gathering:
						return "Gathering";
				}
			}

	};



}

#endif //GAME_UNIT_H
