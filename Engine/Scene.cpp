//
// Created by Sravan Karuturi on 11/6/18.
//

#include "Scene.h"
#include "AssetManager.h"
#include "Window.h"
#include <glm/gtc/matrix_transform.inl>
#include "Colours.h"
#include "Configurations.h"

#include <fstream>

#if ENABLE_GUI
#include "Deps/third_party/Imgui/imgui.h"
#endif

#include "SaveSceneHelpers.h"

namespace vermin
{

    Scene::Scene(std::shared_ptr<Window> _window)
            : window(_window)
    {
        ASMGR.ClearAllData();
        ASMGR.LoadShaders();
        ASMGR.LoadTextures();
    }

    void Scene::HandleInputs()
    {

        window->HandleInput();
        shutDown = glfwWindowShouldClose(window->GetWindow());

    }

}