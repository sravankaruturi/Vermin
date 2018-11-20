//
// Created by Sravan Karuturi on 11/6/2018.
//

#include "library.h"
#include <iostream>
#include "Game.h"

#if defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#endif

int main(){

#if defined(_MSC_VER) && _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    
	v_game::Game g;

	g.Init();

	g.Run();

	g.CleanUp();

	return 0;

}