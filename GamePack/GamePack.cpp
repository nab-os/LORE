//#include "stdafx.h"
#include "GamePack.h"

#include <iostream>

using namespace std;

Library<OpenGL_Window>* GamePack::m__windowLibrary = new Library<OpenGL_Window>();
Library<Scene>* GamePack::m__sceneLibrary = new Library<Scene>();
Library<Camera>* GamePack::m__cameraLibrary = new Library<Camera>();
Library<Object>* GamePack::m__objectLibrary = new Library<Object>();
Library<ModelRender>* GamePack::m__modelRenderLibrary = new Library<ModelRender>();
Library<ModelBullet>* GamePack::m__modelBulletLibrary = new Library<ModelBullet>();
Library<Material>* GamePack::m__materialLibrary = new Library<Material>();
Library<Texture>* GamePack::m__textureLibrary = new Library<Texture>();
Library<Shader>* GamePack::m__shaderLibrary = new Library<Shader>();

GamePack::GamePack()
{

	
}


GamePack::~GamePack()
{



}


void GamePack::error_callback(int error, const char* description)
{
	cout << "[Window] error_callback() :" << description << "\n";
}


int GamePack::init()
{

	glfwSetErrorCallback(GamePack::error_callback);

	if (!glfwInit()) {

		std::cout << "Failed to initialize GLFW\n";
		return -1;

	}

	// On initialise GLEW
	GLenum initialisationGLEW(glewInit());

	// Si l'initialisation a échoué :
	if (initialisationGLEW != GLEW_OK)
	{

		// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
		std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

		glfwTerminate();
		exit(EXIT_FAILURE);

		return false;
	}

	return true;
}


void GamePack::unload()
{

	/*GamePack::m__windowLibrary->flush();
	GamePack::m__sceneLibrary->flush();
	GamePack::m__cameraLibrary->flush();
	GamePack::m__objectLibrary->flush();
	GamePack::m__modelRenderLibrary->flush();
	GamePack::m__modelBulletLibrary->flush();
	GamePack::m__materialLibrary->flush();
	GamePack::m__textureLibrary->flush();
	GamePack::m__shaderLibrary->flush();*/
}


OpenGL_Window* GamePack::createWindow(string id, string name)
{

	OpenGL_Window* w = new OpenGL_Window(name);

	//GamePack::m__windowLibrary->add(id, w);

	return w;

}


Scene* GamePack::createScene(string id, string name)
{

	Scene* s = new Scene(/*name*/);

	//GamePack::m__sceneLibrary->add(id, s);

	return s;

}


Camera* GamePack::createCamera(string id, string name)
{

	Camera* c = new Camera(/*name*/);

	//GamePack::m__cameraLibrary->add(id, c);

	return c;

}


Object* GamePack::createObject(string id, string name)
{

	Object* o = new Object(/*name*/);

	//GamePack::m__objectLibrary->add(id, o);

	return o;

}


ModelRender* GamePack::createModelRender(string id, string name)
{

	ModelRender* m = new ModelRender(/*name*/);

	//GamePack::m__modelRenderLibrary->add(id, m);

	return m;

}


ModelBullet* GamePack::createModelBullet(string id, string name)
{

	ModelBullet* m = new ModelBullet(/*name*/);

	//GamePack::m__modelBulletLibrary->add(id, m);

	return m;

}


Material* GamePack::createMaterial(string id, string name)
{

	Material* m = new Material(/*name*/);

	//GamePack::m__materialLibrary->add(id, m);

	return m;

}


Texture* GamePack::createTexture(string id, string name)
{

	Texture* t = new Texture(/*name*/);

	//GamePack::m__textureLibrary->add(id, t);

	return t;

}


Shader* GamePack::createShader(string id, string name)
{

	Shader* s = new Shader(/*name*/);

	//GamePack::m__shaderLibrary->add(id, s);

	return s;

}

