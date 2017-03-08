#ifndef LORE_H
#define LORE_H

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Library.h"
#include "Importer.h"

#include "Window.h"
#include "Scene.h"
#include "Controller.h"
#include "ModelRender.h"
#include "Material.h"
//#include "Effect.h"
#include "Texture.h"
//#include "Light.h"
#include "Camera.h"
#include "Shader.h"

namespace LORE
{

    class Lore
    {

        public:

            static LORE::Window* init();
            static void unload();

            static Window* createWindow(std::string id, std::string name);
            static bool importScene(std::string id, Scene* scene);
            static bool importCamera(std::string id, Camera* cam);
            static bool importObject(std::string id, Object* obj);
            static bool importMesh(std::string id, Mesh* mesh);
            static Material* createMaterial(std::string id, std::string name);
            static Texture* createTexture(std::string id, std::string name);
            static Shader* createShader(std::string id, std::string name);

            static Camera* load(std::string path);

            static Mesh* getMesh(std::string id);

        private:

            Lore();
            virtual ~Lore();

            static void error_callback(int error, const char* description);

            static Library<Window>* m__windowLibrary;
            static Library<Scene>* m__sceneLibrary;
            static Library<Camera>*	m__cameraLibrary;
            static Library<Object>*	m__objectLibrary;
            static Library<Mesh>* m__meshLibrary;
            static Library<Material>* m__materialLibrary;
            static Library<Texture>* m__textureLibrary;
            static Library<Shader>* m__shaderLibrary;

    };

}

#endif
