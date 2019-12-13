#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Library.h"
#include "Importer.h"

#include "Window.h"
#include "Scene.h"
#include "Node.h"
#include "Object.h"
#include "Controller.h"
#include "ModelRender.h"
#include "Material.h"
//#include "Effect.h"
#include "Texture.h"
//#include "Light.h"
#include "Camera.h"
#include "Shader.h"

using std::string;
using LORE::Texture;
using LORE::Scene;
using LORE::Camera;
using LORE::Node;
using LORE::Mesh;
using LORE::Material;
using LORE::Texture;
using LORE::Shader;
using LORE::Library;
using LORE::Object;

namespace LORE{
    class Lore {
        public:
            static LORE::Window* init();
            static void unload();

            static Window* createWindow(string id, string name);
            static bool importScene(string id, Scene* scene);
            static bool importNode(string id, Node* node);
            static bool importMesh(string id, Mesh* mesh);
            static Scene* createScene(string id);
            static Node* createNode(string id);
            static Object* createObject(string id);
            static Camera* createCamera(string id);
            static Mesh* createMesh(string id);
            static Material* createMaterial(string id);
            static Texture* createTexture(string id);
            static Shader* createShader(string id);

            static Scene* load(string path);

            static Scene* getScene(string id);
            static Camera* getCamera(string id);
            static void listCameras();
            static Node* getNode(string id);
            static Mesh* getMesh(string id);
            static Texture* getTexture(string id);
            static Material* getMaterial(string id);
            static Shader* getShader(string id);

        private:
            Lore();
            virtual ~Lore();

            static void error_callback(int error, const char* description);

            static Library<Window>* m__windowLibrary;
            static Library<Scene>* m__sceneLibrary;
            static Library<Camera>* m__cameraLibrary;
            static Library<Node>*	m__nodeLibrary;
            static Library<Mesh>* m__meshLibrary;
            static Library<Material>* m__materialLibrary;
            static Library<Texture>* m__textureLibrary;
            static Library<Shader>* m__shaderLibrary;
    };
}
