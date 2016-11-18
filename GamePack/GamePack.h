#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Library.h"

#include "OpenGL_Window.h"
#include "Scene.h"
#include "Controller.h"
#include "ModelRender.h"
#include "ModelBullet.h"
#include "Material.h"
//#include "Effect.h"
#include "Texture.h"
//#include "Light.h"
#include "Camera.h"
#include "Shader.h"

class GamePack
{

	public:

		static OpenGL_Window* init();
		static void unload();

		static OpenGL_Window* createWindow(std::string id, std::string name);
		static Scene* createScene(std::string id, std::string name);
		static Camera* createCamera(std::string id, std::string name);
		static Object* createObject(std::string id, std::string name);
		static ModelRender* createModelRender(std::string id, std::string name);
		static ModelBullet* createModelBullet(std::string id, std::string name);
		static Material* createMaterial(std::string id, std::string name);
		static Texture* createTexture(std::string id, std::string name);
		static Shader* createShader(std::string id, std::string name);

	private:

		GamePack();
		virtual ~GamePack();

		static void error_callback(int error, const char* description);

		static Library<OpenGL_Window>* 	m__windowLibrary;
		static Library<Scene>* 			m__sceneLibrary;
		static Library<Camera>* 		m__cameraLibrary;
		static Library<Object>* 		m__objectLibrary;
		static Library<ModelRender>* 	m__modelRenderLibrary;
		static Library<ModelBullet>* 	m__modelBulletLibrary;
		static Library<Material>* 		m__materialLibrary;
		static Library<Texture>* 		m__textureLibrary;
		static Library<Shader>* 		m__shaderLibrary;

};
