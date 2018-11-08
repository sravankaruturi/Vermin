//
// Created by Sravan Karuturi on 11/6/2018.
//

#include <iostream>
#include "../Engine/library.h"

#if defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#endif

int main(){

#if defined(_MSC_VER)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    hello();

	return 0;

}