#include "library.h"
#include "TestScene.h"
#include "LoggingManager.h"
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#if defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#endif

void hello() {

#if defined(_MSC_VER)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    std::cout << "Started the application." << std::endl;

	std::shared_ptr<vermin::Window> w = std::make_shared<vermin::Window>(800, 600, "Vermin Engine");

	/* ImGui setup */
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(w->GetWindow(), false);
	ImGui_ImplOpenGL3_Init();

	// Setup style
	ImGui::StyleColorsDark();

	vermin::ImGuiLog imgui_logger;
	LOGGER.SetImGuiLogger(&imgui_logger);

    std::unique_ptr<vermin::TestScene> t = std::make_unique<vermin::TestScene>(w);

    while( !t->ShutDown()){
        t->RunScene();
    }

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

}