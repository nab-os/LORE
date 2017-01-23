//#include "stdafx.h"
#include "Lore.h"

#include <iostream>

using namespace std;

Library<OpenGL_Window>* Lore::m__windowLibrary = new Library<OpenGL_Window>();
Library<Scene>* Lore::m__sceneLibrary = new Library<Scene>();
Library<Camera>* Lore::m__cameraLibrary = new Library<Camera>();
Library<Object>* Lore::m__objectLibrary = new Library<Object>();
Library<ModelRender>* Lore::m__modelRenderLibrary = new Library<ModelRender>();
//Library<ModelBullet>* Lore::m__modelBulletLibrary = new Library<ModelBullet>();
Library<Material>* Lore::m__materialLibrary = new Library<Material>();
Library<Texture>* Lore::m__textureLibrary = new Library<Texture>();
Library<Shader>* Lore::m__shaderLibrary = new Library<Shader>();

Lore::Lore()
{


}


Lore::~Lore()
{



}


void Lore::error_callback(int error, const char* description)
{
	cout << "[Window] error_callback() :" << description << "\n";
}

/**
 * Initialize Glfw and Glew and returns an OpenGL_Window
 * @return returns a window
 **/
OpenGL_Window* Lore::init()
{

	cout << "[Lore] init" << endl;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {

		std::cout << "Failed to initialize GLFW\n";
		return nullptr;

	}

	//=====================

	OpenGL_Window* w = Lore::createWindow("Window_1", "Test");
	w->load();

	//=====================

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// On initialise GLEW
	GLenum initialisationGLEW(glewInit());

	// Si l'initialisation a échoué :
	if (initialisationGLEW != GLEW_OK)
	{

		// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
		std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

		glfwTerminate();
		exit(EXIT_FAILURE);

	}

	return w;
}


void Lore::unload()
{

	Lore::m__windowLibrary->flush();
	Lore::m__sceneLibrary->flush();
	Lore::m__cameraLibrary->flush();
	Lore::m__objectLibrary->flush();
	Lore::m__modelRenderLibrary->flush();
//	Lore::m__modelBulletLibrary->flush();
	Lore::m__materialLibrary->flush();
	Lore::m__textureLibrary->flush();
	Lore::m__shaderLibrary->flush();

	glfwTerminate();

}


OpenGL_Window* Lore::createWindow(string id, string name)
{

	OpenGL_Window* w = new OpenGL_Window(name);

	Lore::m__windowLibrary->add(id, w);

	return w;

}


Scene* Lore::createScene(string id, string name)
{

	Scene* s = new Scene(/*name*/);

	Lore::m__sceneLibrary->add(id, s);

	return s;

}


Camera* Lore::createCamera(string id, string name)
{

	Camera* c = new Camera(/*name*/);

	Lore::m__cameraLibrary->add(id, c);

	return c;

}


Object* Lore::createObject(string id, string name)
{

	Object* o = new Object(/*name*/);

	Lore::m__objectLibrary->add(id, o);

	return o;

}


ModelRender* Lore::createModelRender(string id, string name)
{

	ModelRender* m = new ModelRender(/*name*/);

	Lore::m__modelRenderLibrary->add(id, m);

	return m;

}

/*
ModelBullet* Lore::createModelBullet(string id, string name)
{

	ModelBullet* m = new ModelBullet(name);

	Lore::m__modelBulletLibrary->add(id, m);

	return m;

}*/


Material* Lore::createMaterial(string id, string name)
{

	Material* m = new Material(/*name*/);

	Lore::m__materialLibrary->add(id, m);

	return m;

}


Texture* Lore::createTexture(string id, string name)
{

	Texture* t = new Texture(/*name*/);

	Lore::m__textureLibrary->add(id, t);

	return t;

}


Shader* Lore::createShader(string id, string name)
{

	Shader* s = new Shader(/*name*/);

	Lore::m__shaderLibrary->add(id, s);

	return s;

}


void Lore::load(string path)
{

    Loader::load(path, Lore::m__windowLibrary, Lore::m__sceneLibrary, Lore::m__cameraLibrary, Lore::m__objectLibrary, Lore::m__modelRenderLibrary, /*Lore::m__modelBulletLibrary,*/ Lore::m__materialLibrary, Lore::m__textureLibrary, Lore::m__shaderLibrary);

}
