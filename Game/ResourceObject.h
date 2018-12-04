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


			bool MineResources(int _amount){
				if ( this->resourceAmount >= _amount ){
					this->resourceAmount -= _amount;
					return true;
				}
				return false;
			}

	};


}

