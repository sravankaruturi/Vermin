//
// Created by Sravan Karuturi on 11/7/18.
//

#pragma once

#include <memory>
#include <map>

#if _WIN32 && !defined(_MSC_VER)

#include <dirent.h>
#include <vector>
#include <sstream>
#include <iostream>

#else
#include <filesystem>
#endif

#include "Texture.h"
#include "GLShader.h"
#include "FolderLocations.h"

#include "LoggingManager.h"
#include "PE_GL.h"


#ifdef _DEBUG
/*@see https://msdn.microsoft.com/en-us/library/x98tx3cf.aspx */
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#define ASMGR vermin::AssetManager::getInstance()

namespace vermin {

    class Object;

    class AssetManager {
    public:
        /**
        * \brief Returns the instance of the Singleton.
        * \return The reference to the static object, instance.
        */
        static AssetManager &getInstance() {
            static AssetManager instance; // Guaranteed to be destroyed and Instantiated on first use.
            return instance;
        }

        void ClearAllData() {
            //for (auto it : textures)
            //{
            //	delete it.second;
            //}

            ///*for (auto it : shaders)
            //{
            //	delete it.second;
            //}*/

            //for (auto it: objects)
            //{
            //	// This is not an error since we have a properly defined destructor.
            //	// @see https://stackoverflow.com/questions/4325154/delete-objects-of-incomplete-type#4325223
            //	// This is because of the Forward Declaration.
            //	delete it.second;
            //}

            textures.clear();
            shaders.clear();
            objects.clear();
        }

        /**
        * \brief Default Constructor.
        */
        //AssetManager() = default;

        /**
        * \brief Destructor. Deletes all the Shaders and Textures stored here.
        */
        ~AssetManager() {
            ClearAllData();
        }

        /**
        * \brief A Map of all the shaders that we load.
        */
        std::map<std::string, std::shared_ptr<GLShader>> shaders;
        /**
        * \brief A Map of all the textures that we load.
        */
        std::map<std::string, std::shared_ptr<Texture>> textures;

        /**
        * \brief A Map of all the Renderables loaded.
        */
        std::map<std::string, std::shared_ptr<Object>> objects;

        /**
        * \brief The Shader Directory from where all the shaders are loaded.
        */
        std::string shaderDir = SHADER_FOLDER;
        /**
        * \brief The Texture Directory from where all the Textures are loaded.
        */
        std::string textureDir = TEXTURE_FOLDER;

        /**
        * \brief Loads all the shaders from the Shader Directory.
        */
        bool LoadShaders() {
            LOGGER.AddToLog("Loading Shaders...");
            // Load all the shaders in the directory and compile them.
#if _WIN32 && !defined(_MSC_VER)
            DIR *dp = opendir(shaderDir.c_str());
            struct dirent *dirp;
            while ((dirp = readdir(dp)) != NULL) {
                std::string complete_file_name = std::string(dirp->d_name);
                std::string extension;
                std::stringstream ss;
                ss.str(complete_file_name);
                while (getline(ss, extension, '.')) {
                }
                extension = "." + extension;
#else
                for (auto &p : std::experimental::filesystem::directory_iterator(shaderDir)) {
                        std::string extension = p.path().extension().generic_string();
                        std::string complete_file_name = p.path().generic_string().c_str();
#endif
                // *. Check only vert extensions.

                if ( complete_file_name == "." || complete_file_name == ".."){
                    continue;
                }

                if (".vert" != extension && ".shader" != extension) {
                    if (".frag" != extension) {
                        // Extensions should be Vert or Frag.
                        return false;
                    }
                    continue;
                }

                try {
#if _WIN32 && !defined(_MSC_VER)
                    std::string file_name;
                    file_name = complete_file_name.substr(0, complete_file_name.length() - extension.length());
#else
                    std::string file_name = p.path().filename().generic_string();
#endif


                    // Important: This only works if the file extension is .vert.
//                    if (".vert" == extension) {
//                        for (auto i = 0; i < 5; i++)
//                            file_name.pop_back();
//                    } else if (".shader" == extension) {
//                        for (auto i = 0; i < 7; i++)
//                            file_name.pop_back();
//                    }


                    // *. Get the key for the Map.
                    // *. Check if the Shader already exists and skip if it does log the anamoly.
                    if (this->shaders.count(file_name)) {
                        continue;
                    }

                    if (".vert" == extension) {
                        // *. Get the second file as well.
                        // *. Create the Shader and load it in the map.
                        this->shaders.insert(
                                std::make_pair(
                                file_name,
                                std::make_shared<GLShader>(
                                        shaderDir + complete_file_name,
                                        (shaderDir + file_name + std::string(".frag")).c_str()
                                        )
                                        )
                                        );
                    } else if (".shader" == extension) {
                        this->shaders.insert(
                                std::make_pair(
                                        file_name,
                                        std::make_shared<GLShader>(shaderDir + complete_file_name)
                                )
                        );
                    }

                    LOGGER.AddToLog("Loaded " + file_name + " Shader.");

                }
                catch (...) {
                    return false;
                }

            }

            LOGGER.AddToLog("Loaded Shaders Successfully. \n");

            return true;
        }

        /**
        * \brief Loads all the Textures from the Texture Directory.
        */
        bool LoadTextures() {
            LOGGER.AddToLog("Loading Textures..");



#if _WIN32 && !defined(_MSC_VER)
            DIR *dp = opendir(shaderDir.c_str());
            struct dirent *dirp;
            while ((dirp = readdir(dp)) != NULL) {
                std::string complete_file_name = std::string(dirp->d_name);

                if (complete_file_name == "." || complete_file_name == ".."){
                    continue;
                }

                std::string extension;
                std::stringstream ss;
                ss.str(complete_file_name);
                while (getline(ss, extension, '.')) {
                }
                extension = "." + extension;
#else
                for (auto &p : std::experimental::filesystem::directory_iterator(shaderDir)) {
                        std::string extension = p.path().extension().generic_string();
                        std::string complete_file_name = p.path().generic_string().c_str();
#endif

                std::string file_name;
                try {
#if _WIN32 && !defined(_MSC_VER)
                    file_name = complete_file_name.substr(0, complete_file_name.length() - extension.length());
#else
                    file_name = p.path().filename().generic_string();
#endif
                    while (file_name.back() != '.') {
                        file_name.pop_back();
                    }
                    file_name.pop_back();

                    this->textures.insert(
                            std::make_pair(file_name, std::make_shared<Texture>(textureDir + complete_file_name))
                    );
                }
                catch (...) {
                    return false;
                }
                LOGGER.AddToLog("Loaded " + file_name + " Texture");
            }

            LOGGER.AddToLog("Loaded Textures.. \n");

            return true;
        }

        /**
        * \brief Returns if the texture, key is loaded.
        * \param _key The string, key to look for in the map.
        * \return Returns True if we can find the texture in the map.
        */
        bool IsTextureLoaded(std::string _key) {
            return (!(textures.find(_key) == textures.end()));
        }

        /**
        * \brief Returns if the mesh is loaded.
        * \param _key Key
        * \return True if we find the mesh with the key.
        */
        bool IsObjectLoaded(std::string _key) {
            return (!(objects.find(_key) == objects.end()));
        }

        /**
        * \brief Add a texture to the exisiting map.
        * \param _name The Key to place the Texture.
        * \param _texture The Texture to load and place.
        * \return Returns true if the Texture is succesfully loaded. False if something occurs.
        */
        bool AddToTextures(const std::string &_name, std::shared_ptr<Texture> _texture) {
            if (IsTextureLoaded(_name)) return false;
            try {
                this->textures.insert(
                        std::make_pair(_name, _texture)
                );
                LOGGER.AddToLog("Adding " + _name + " to textures.");
            }
            catch (...) {
                return false;
            }
            return true;
        }

        bool AddToObjects(const std::string &_name, std::shared_ptr<Object> _object) {
            if (IsObjectLoaded(_name)) return false;
            try {
                this->objects.insert(std::make_pair(_name, _object));
                LOGGER.AddToLog("Adding " + _name + " to Objects.");
            }
            catch (...) {
                return false;
            }
            return true;
        }


        void GuiRender(bool *_windowFlag) {
            // A Hierarchy listing all the Assets currently in the ASMGR.
            ImGui::Begin("Asset Manager Details", _windowFlag);
            ImGui::Columns(1);
            if (ImGui::CollapsingHeader("Shaders")) {
                for (auto it : this->shaders) {
                    ImGui::Columns(2);
                    ImGui::Text(it.first.c_str());
                    ImGui::NextColumn();
                    ImGui::Text("%d", it.second->shaderId);
                    ImGui::NextColumn();
                }
            }

            ImGui::Columns(1);
            if (ImGui::CollapsingHeader("Textures")) {
                for (auto it : this->textures) {
                    ImGui::Columns(3);
                    ImGui::Text(it.first.c_str());
                    ImGui::NextColumn();
                    ImGui::Text("%d", it.second->GetTextureId());
                    ImGui::NextColumn();
                    ImGui::Image((void *) it.second->GetTextureId(), ImVec2(30, 30));
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Image((void *) it.second->GetTextureId(), ImVec2(200, 200));
                        ImGui::EndTooltip();
                    }
                    ImGui::NextColumn();
                }
            }
            ImGui::End();

        }


    };

}


