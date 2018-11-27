//
// Created by skk7174 on 11/12/2018.
//

#include "Unit.h"
#include "AssetManager.h"

namespace v_game {

	Unit::Unit(UnitType _type)
		: AnimatedEntity("Unit", "Villager/Worker_Happy_Idle.FBX", "unit", glm::vec3(-10, 0, -10), glm::vec3(10, 50, 10)), type(_type)
	{

		this->objectName = animation_names[static_cast<int>(_type)][static_cast<int>(AnimType::idle)];

		this->idleObjectName = animation_names[static_cast<int>(_type)][static_cast<int>(AnimType::idle)];
		this->walkObjectName = animation_names[static_cast<int>(_type)][static_cast<int>(AnimType::walking)];
		this->deathObjectName = animation_names[static_cast<int>(_type)][static_cast<int>(AnimType::death)];
		this->attackObjectName = animation_names[static_cast<int>(_type)][static_cast<int>(AnimType::attack)];

		this->SetScale(glm::vec3(1 / 64.0f));
		this->SetRotation(glm::vec3(0, 0, 0));

		switch (_type)
		{
		case UnitType::villager:
			this->gPlay.health = 50;
			this->gPlay.maxHealth = 100;
			this->faceTextureID = ASMGR.textures.at("WorkerFace")->GetTextureId();
			break;
		case UnitType::warrior:
			this->gPlay.health = 29;
			this->gPlay.maxHealth = 120;
			this->faceTextureID = ASMGR.textures.at("KnightFace")->GetTextureId();
			break;
		default:
			this->gPlay.health = 0;
			this->gPlay.maxHealth = 0;
			this->faceTextureID = 0;
			break;
		}

	}

	float Unit::GetCurrentHPPerc()
	{
		return (float)this->gPlay.health/this->gPlay.maxHealth;
	}

	void Unit::Update(float _deltaTime, vermin::Terrain * _terrain)
	{

		if ( !this->gPlay.active )
		{
			return;
		}

		if ( this->gPlay.toBeDeleted)
		{
			if ( this->objectName != deathObjectName)
			{
				this->objectName = deathObjectName;
			}
		}

		AnimatedEntity::Update(_deltaTime);

		if ( this->gPlay.health <= 0 && this->gPlay.active && !this->gPlay.toBeDeleted)
		{
			// Mark for Deletion.
			this->gPlay.toBeDeleted = true;
			this->SetObjectName(deathObjectName);
			this->gPlay.attacker->gPlay.attackingMode = false;
			this->SetAnimationTotalTime(0.0f);
		}

		this->position.y = _terrain->GetHeightAtPos(this->position.x, this->position.z);

		_terrain->GetTileFromIndices(_terrain->GetNodeIndicesFromPos(position))->occupiedBy = static_cast<Entity *>(this);



		/* Pathing */
		glm::vec3 endPosition = _terrain->GetTileFromIndices(this->targetNode)->GetPosition();
        // Update the Target based position.
        if ( this->gPlay.attackTarget != nullptr ){
            endPosition = this->gPlay.attackTarget->GetPosition();
        }

		path = _terrain->GetPathFromPositions(this->position, endPosition);



		if ( this->gPlay.attackingMode ){

			path.pop_back();

			if ( path.size() < 2 ){

				// Start Attacking
				this->currentState = UnitState::attacking;
				this->SetObjectName(attackObjectName);
				this->gPlay.attackTarget->TakeDamage(_deltaTime * this->gPlay.attackDamage);
				this->gPlay.attackTarget->gPlay.attacker = this;

			}

		}
		else {
			if (path.empty())
			{
				if (idleObjectName != this->objectName && deathObjectName != this->objectName)
				{
					this->SetAnimationTotalTime(0);
					//this->SetObjectName("HappyIdle");
					this->SetObjectName(idleObjectName);
				}
			}
			else
			{
				if (walkObjectName != this->objectName)
				{
					this->SetAnimationTotalTime(0);
					this->SetObjectName(walkObjectName);
				}
			}
		}

		// To remove attackers.. Each entity can check if the attacker still exists and is still attacking?
		totalTimeCounterForPathing += _deltaTime;

		if (totalTimeCounterForPathing < 1.0f && !path.empty()) {

			// Get the Current Node.
			glm::vec2 start_indices = _terrain->GetNodeIndicesFromPos(this->position.x, this->position.z);
			auto start_tile = _terrain->GetTileFromIndices(start_indices.x, start_indices.y);

			// Look for the Next Node.
			auto next_tile = path.back();



			// Traverse the Distance b/w them * deltaTime. --> You complete the distance two nodes in 1 second.
			glm::vec3 final_position = this->position + ((next_tile->GetPosition() - this->position) * _deltaTime * this->movementSpeed);

			// Get the Rotation, about, y ,axis, with both the nodes.
			// Get the Vector, Target Node - Current Node.
			// The Inverse of Dot Product b/w that and X Axis, should be the angle?
			glm::vec3 target_direction = glm::normalize(final_position - this->position);
			glm::vec3 x_axis = glm::vec3(0, 0, 1);

			rotation.y = (target_direction.x > 0) ? glm::degrees(glm::acos(glm::dot(target_direction, x_axis))) : (360 - glm::degrees(glm::acos(glm::dot(target_direction, x_axis))));

			position.x = final_position.x;
			position.z = final_position.z;

		}
		else if (totalTimeCounterForPathing > 1.0f) {
			totalTimeCounterForPathing = 0.0f;
		}

	}

	UnitState Unit::getCurrentState() const {
		return currentState;
	}

	void Unit::setCurrentState(UnitState currentState) {
		Unit::currentState = currentState;
	}
}
