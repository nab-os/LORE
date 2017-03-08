#include "Scene.h"

#include <iostream>

#include "Camera.h"

using namespace std;
using namespace glm;
using namespace LORE;

Scene::Scene(int width, int height):	Object(),
										m__paused(false),
										m__environmentMap(),
										m__lights()
{

	cout << this << " [Scene] constructor" << endl;

}


Scene::~Scene()
{

	cout << this << " [ModelRender] destructor" << endl;

    if(m__environmentMap)
		delete m__environmentMap;

}


void Scene::load()
{

	cout << this << " [Scene] load" << endl;

    m__environmentMap = new CubeMap();
	m__environmentMap->load();

    Object::load();

}


void Scene::render(mat4 &projection, mat4 &view, mat4 &model)
{

	this->renderObjects(projection, view, model);

}


void Scene::renderObjects(mat4 &projection, mat4 &view, mat4 &model)
{

	mat4 saveModel = model;

	Object::render(projection, view, model, m__environmentMap->getID());

	model = saveModel;

}


void Scene::renderLights()
{



}

