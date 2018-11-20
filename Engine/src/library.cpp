#include "library.h"

#if defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#endif

void hello() {

#if defined(_MSC_VER)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    std::cout << "Started the application." << std::endl;

	std::shared_ptr<vermin::Window> w = std::make_shared<vermin::Window>(800, 600, "Vermin Engine");

#if ENABLE_GUI

	/* ImGui setup */
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(w->GetWindow(), false);
	ImGui_ImplOpenGL3_Init();

	// Setup style
	ImGui::StyleColorsDark();

	vermin::ImGuiLog imgui_logger;
	LOGGER.SetImGuiLogger(&imgui_logger);

#endif

    std::unique_ptr<vermin::TestScene> t = std::make_unique<vermin::TestScene>(w);

    while( !t->ShutDown()){
        t->RunScene();
    }

#if ENABLE_GUI

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

#endif

}