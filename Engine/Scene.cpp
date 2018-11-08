//
// Created by Sravan Karuturi on 11/6/18.
//

#include "Scene.h"
#include "AssetManager.h"
#include "Window.h"

#if ENABLE_GUI
#include "Deps/third_party/Imgui/imgui.h"
#endif

namespace vermin
{

    Scene::Scene(std::shared_ptr<Window> _window)
            : window(std::move(_window))
    {
        ASMGR.ClearAllData();
        ASMGR.LoadShaders();
        ASMGR.LoadTextures();
    }

    void Scene::HandleInputs()
    {

        window->HandleInput();
        shutDown = glfwWindowShouldClose(window->GetWindow()) & 1;

    }

}