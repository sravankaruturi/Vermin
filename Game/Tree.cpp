//
// Created by Sravan Karuturi on 11/28/18.
//

#include "Tree.h"
#include "FolderLocations.h"

namespace v_game{

	Tree::Tree(glm::vec3 _position)
	: Entity("Tree", "Medieval_House/Medieval_House.obj", "town_center", glm::vec3(-120, 0, -120), glm::vec3(150, 200, 200)), ResourceObject(100)
	{
		this->SetScale(glm::vec3(1/512.0f));
		this->SetPosition(_position);
	}

	void Tree::Update(float _deltaTime){

		//this->SetScale(this->GetScale() * ((resourceAmount)/100.0f) );
		if ( this->resourceAmount <= 0.0f ){
			this->gPlay.active = false;
		}

		Entity::Update(_deltaTime);

	}
}
