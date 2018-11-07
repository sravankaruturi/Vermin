#include "library.h"

#include <iostream>

void hello() {
    std::cout << "Hello, World!" << std::endl;

    vermin::Window w = vermin::Window(400, 400, "Vermin Engine");

    while(true){
        w.Update(0);
    }
}