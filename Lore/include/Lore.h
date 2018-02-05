#ifndef LORE_H
#define LORE_H

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

namespace LORE
{

    class Lore
    {

        public:

            static LORE::Window* init();
            static void unload();

            static Window* createWindow(std::string id, std::string name);
            static bool importScene(std::string id, Scene* scene);
            static bool importNode(std::string id, Node* node);
            static bool importMesh(std::string id, Mesh* mesh);
            static Scene* createScene(std::string id);
            static Node* createNode(std::string id);
            static Object* createObject(std::string id);
            static Camera* createCamera(std::string id);
            static Mesh* createMesh(std::string id);
            static Material* createMaterial(std::string id);
            static Texture* createTexture(std::string id);
            static Shader* createShader(std::string id);

            static Scene* load(std::string path);

            static Scene* getScene(std::string id);
            static Node* getNode(std::string id);
            static Mesh* getMesh(std::string id);
            static Texture* getTexture(std::string id);
            static Material* getMaterial(std::string id);
            static Shader* getShader(std::string id);

        private:

            Lore();
            virtual ~Lore();

            static void error_callback(int error, const char* description);

            static Library<Window>* m__windowLibrary;
            static Library<Scene>* m__sceneLibrary;
            static Library<Node>*	m__nodeLibrary;
            static Library<Mesh>* m__meshLibrary;
            static Library<Material>* m__materialLibrary;
            static Library<Texture>* m__textureLibrary;
            static Library<Shader>* m__shaderLibrary;

    };

}

#endif
