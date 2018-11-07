#include "library.h"

#include <iostream>

void hello() {

    std::cout << "Started the application." << std::endl;

    std::unique_ptr<vermin::Window> w = std::make_unique<vermin::Window>(400, 400, "Vermin Engine");



    while(true){
        w->Update(0);
    }


}