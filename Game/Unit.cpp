//
// Created by skk7174 on 11/12/2018.
//

#include "Unit.h"
#include "LoggingManager.h"
#include "AssetManager.h"

namespace v_game {

	Unit::Unit(UnitType _type)
		: AnimatedEntity("Unit", "Villager/Worker_Happy_Idle.FBX", "unit", glm::vec3(-10, 0, -10), glm::vec3(10, 50, 10))
	{

		this->objectName = animation_names[static_cast<int>(_type)][static_cast<int>(AnimType::idle)];

		this->idleObjectName = animation_names[static_cast<int>(_type)][static_cast<int>(AnimType::idle)];
		this->walkObjectName = animation_names[static_cast<int>(_type)][static_cast<int>(AnimType::walking)];
		this->deathObjectName = animation_names[static_cast<int>(_type)][static_cast<int>(AnimType::death)];

		this->SetScale(glm::vec3(1 / 64.0f));
		this->SetRotation(glm::vec3(0, 0, 0));

		switch (_type)
		{
		case UnitType::villager:
			this->health = 50;
			this->maxHealth = 100;
			this->faceTextureID = ASMGR.textures.at("WorkerFace")->GetTextureId();
			break;
		case UnitType::warrior:
			this->health = 29;
			this->maxHealth = 120;
			this->faceTextureID = ASMGR.textures.at("KnightFace")->GetTextureId();
			break;
		default:
			this->health = 0;
			this->maxHealth = 0;
			this->faceTextureID = 0;
			break;
		}

	}

	float Unit::GetCurrentHPPerc()
	{
		return (float)health / maxHealth;
	}

	void Unit::Update(float _deltaTime, vermin::Terrain * _terrain)
	{

		AnimatedEntity::Update(_deltaTime);

		this->position.y = _terrain->GetHeightAtPos(this->position.x, this->position.z);

		_terrain->GetTileFromIndices(_terrain->GetNodeIndicesFromPos(position))->occupiedBy = static_cast<Entity *>(this);



		/* Pathing */

		glm::vec3 endPosition = _terrain->GetTileFromIndices(this->targetNode)->GetPosition();

		_terrain->HighlightNode(this->targetNode.x, this->targetNode.y);

		path = _terrain->GetPathFromPositions(this->position, endPosition);

		/*std::string log_temp = "The path b/w the tiles, ";

		log_temp += Vec3ToString(startPosition) + " and " + Vec3ToString(endPosition) + " has " + std::to_string(path.size()) + " nodes";*/

		////if (it->gPlay.attackingMode && !path.empty()) {
		////	// If you are attacking, you stop one tile before the actual target.
		////	path.pop_back();
		////}

		////if (it->gPlay.attackingMode) {

		////	// Close enough
		////	if (path.size() < 2 && it->gPlay.attackTarget->gPlay.attacker == nullptr)
		////	{
		////		it->gPlay.attackTarget->gPlay.attacker = it.get();
		////		// That object immediately starts attacking the current player.
		////		it->gPlay.attackTarget->gPlay.attackingMode = true;
		////		it->gPlay.attackTarget->gPlay.attackTarget = it.get();
		////		if ("SwordAndShieldSlash" != it->GetObjectName() && "Dying" != it->GetObjectName())
		////		{
		////			it->SetAnimationTotalTime(0);
		////			it->SetObjectName("SwordAndShieldSlash");
		////		}
		////	}
		////	else if (path.size() > 2 && it->gPlay.attackTarget->gPlay.attacker == it.get())
		////	{
		////		it->gPlay.attackTarget->gPlay.attacker = nullptr;

		////		if ("Walking" != it->GetObjectName())
		////		{
		////			it->SetAnimationTotalTime(0);
		////			it->SetObjectName("Walking");
		////		}
		////	}
		////}
		//else
		{
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
}
