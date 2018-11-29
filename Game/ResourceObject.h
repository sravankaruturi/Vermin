//
// Created by Sravan Karuturi on 11/28/18.
//

// This is sort of an Interface for Tree and Stone to Implement

#pragma once

class ResourceObject {

protected:

	int resourceAmount = 0;

	ResourceObject(int _amount) : resourceAmount(_amount){

	}

public :

	virtual void MineResources(int _amount) = 0;

};


