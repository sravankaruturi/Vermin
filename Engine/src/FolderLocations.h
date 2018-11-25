//#define SHADER_FOLDER "../../Engine/Shaders/"
#pragma once

#include "Configurations.h"

#if IS_HOME_PC

#define SHADER_FOLDER			"C:/dev/Vermin/Shaders/"
#define TEXTURE_FOLDER			"C:/dev/Vermin/Assets/Textures/"
#define MODEL_FOLDER			"C:/dev/Vermin/Assets/Models/"
#define SCENES_FOLDER			"C:/dev/Vermin/Assets/Scenes/"
										
#define EXTERNAL_FILES			"C:/dev/Vermin/Engine/Deps/third_party/"

#elif IS_HOME_LINUX

#define SHADER_FOLDER			"/home/ant/projects/Vermin/Shaders/"
#define TEXTURE_FOLDER			"/home/ant/projects/Vermin/Assets/Textures/"
#define MODEL_FOLDER			"/home/ant/projects/Vermin/Assets/Models/"
#define SCENES_FOLDER			"/home/ant/projects/Vermin/Assets/Scenes/"

#define EXTERNAL_FILES			"/home/ant/projects/Vermin/Engine/Deps/third_party/"

#elif MACBOOK

#define SHADER_FOLDER            "/Users/Sravan/ClionProjects/Vermin/Shaders/"
#define TEXTURE_FOLDER            "/Users/Sravan/ClionProjects/Vermin/Assets/Textures/"
#define MODEL_FOLDER            "/Users/Sravan/ClionProjects/Vermin/Assets/Models/"
#define SCENES_FOLDER            "/Users/Sravan/ClionProjects/Vermin/Assets/Scenes/"

#define EXTERNAL_FILES            "/Users/Sravan/ClionProjects/Vermin/Engine/Deps/third_party/"

#elif LAB_MACHINE

#define SHADER_FOLDER            "Z:/IGMProfile/Desktop/Projects/Vermin/Shaders/"
#define TEXTURE_FOLDER            "Z:/IGMProfile/Desktop/Projects/Vermin/Assets/Textures/"
#define MODEL_FOLDER            "Z:/IGMProfile/Desktop/Projects/Vermin/Assets/Models/"
#define SCENES_FOLDER            "Z:/IGMProfile/Desktop/Projects/Vermin/Assets/Scenes/"

#define EXTERNAL_FILES            "Z:/IGMProfile/Desktop/Projects/Vermin/Engine/Deps/third_party/"

#else

#endif