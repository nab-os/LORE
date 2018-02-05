#include "Scene.h"

#include <iostream>

#include "Camera.h"

using namespace std;
using namespace glm;
using namespace LORE;

Scene::Scene():	Node(),
                m__paused(false),
                m__environmentMap(),
                m__lights()
{
	cout << this << " [Scene] constructor" << endl;
}


Scene::~Scene()
{
	cout << this << " [ModelRender] destructor" << endl;
}


void Scene::render(mat4 projection, mat4 view, mat4 model)
{

    //cout << this << " [Scene] render" << endl;
	this->renderNodes(projection, view, model);

}


void Scene::renderNodes(mat4 projection, mat4 view, mat4 model)
{
	mat4 saveModel = model;
	Node::render(projection, view, model);//, m__environmentMap->getID());
	model = saveModel;
}


void Scene::renderLights()
{



}

