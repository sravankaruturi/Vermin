#include "library.h"
#include "TestScene.h"
#include <iostream>
#include <memory>

void hello() {

    std::cout << "Started the application." << std::endl;

    std::shared_ptr<vermin::Window> w = std::make_shared<vermin::Window>(400, 400, "Vermin Engine");

    std::unique_ptr<vermin::TestScene> t = std::make_unique<vermin::TestScene>(w);

    while( !t->ShutDown()){
        t->RunScene();
    }

}