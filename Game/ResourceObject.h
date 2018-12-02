//
// Created by Sravan Karuturi on 11/28/18.
//

// This is sort of an Interface for Tree and Stone to Implement

#pragma once

namespace v_game{

	class ResourceObject {

	public:

			int resourceAmount = 100;

			explicit ResourceObject(int _amount){
				this->resourceAmount = _amount;
			}


			void MineResources(int _amount){
				this->resourceAmount -= _amount;
			}

	};


}

