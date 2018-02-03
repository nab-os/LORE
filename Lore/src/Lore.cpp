#include "Lore.h"

#include <iostream>

using namespace std;
using namespace LORE;

Library<LORE::Window>* Lore::m__windowLibrary = new Library<Window>();
Library<Scene>* Lore::m__sceneLibrary = new Library<Scene>();
Library<Node>* Lore::m__nodeLibrary = new Library<Node>();
Library<Mesh>* Lore::m__meshLibrary = new Library<Mesh>();
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
 * Initialize Glfw and Glew and returns a Window
 * @return returns a window
 **/
LORE::Window* Lore::init()
{

	cout << "[Lore] init" << endl;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {

		std::cout << "Failed to initialize GLFW\n";
		return nullptr;

	}

	//=====================

    LORE::Window* w = Lore::createWindow("Window_1", "Test");
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
	Lore::m__nodeLibrary->flush();
	Lore::m__meshLibrary->flush();
	Lore::m__materialLibrary->flush();
	Lore::m__textureLibrary->flush();
	Lore::m__shaderLibrary->flush();
	glfwTerminate();
}


LORE::Window* Lore::createWindow(string id, string name)
{
    LORE::Window* w = new Window(name);
	Lore::m__windowLibrary->add(id, w);
	return w;
}


bool Lore::importScene(string id, Scene* scene)
{
	Lore::m__sceneLibrary->add(id, scene);
	return true;
}


bool Lore::importNode(string id, Node* node)
{

    cout << "[Lore]: importNode" << endl;
    Lore::m__nodeLibrary->add(id, node);
	return true;
}


bool Lore::importMesh(string id, Mesh* mesh)
{
    cout << "[Lore]: importMesh" << endl;
	Lore::m__meshLibrary->add(id, mesh);
    return true;
}


Scene* Lore::createScene(string id)
{
    Scene* s = new Scene();
    Lore::m__sceneLibrary->add(id, s);
    return s;
}


Node* Lore::createNode(string id)
{
    Node* n = new Node();
    Lore::m__nodeLibrary->add(id, n);
    return n;
}


Object* Lore::createObject(string id)
{
    Object* o = new Object();
    Lore::m__nodeLibrary->add(id, o);
    return o;
}


Camera* Lore::createCamera(string id)
{
    Camera* c = new Camera();
    Lore::m__nodeLibrary->add(id, c);
    return c;
}


Mesh* Lore::createMesh(string id)
{
    Mesh* o = new Mesh();
    Lore::m__meshLibrary->add(id, o);
    return o;
}


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


Camera* Lore::load(string path)
{
    Importer importer(path);
    importer.import();
    return NULL;
}


Node* Lore::getNode(string id)
{
    return m__nodeLibrary->get(id);
}


Mesh* Lore::getMesh(string id)
{
    return m__meshLibrary->get(id);
}
