#ifndef VERMIN_LIBRARY_H
#define VERMIN_LIBRARY_H

#include "../Configurations.h"
#include "Window.h"
#include "TestScene.h"
#include "LoggingManager.h"
#include "AssetManager.h"
#include "PE_GL.h"

#if ENABLE_GUI
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#endif

void hello();

#endif