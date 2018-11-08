#include "library.h"
#include "TestScene.h"

#if defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#endif

void hello() {

#if defined(_MSC_VER)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    std::cout << "Started the application." << std::endl;

	std::shared_ptr<vermin::Window> w = std::make_shared<vermin::Window>(800, 600, "Vermin Engine");

    std::unique_ptr<vermin::TestScene> t = std::make_unique<vermin::TestScene>(w);

    while( !t->ShutDown()){
        t->RunScene();
    }

}