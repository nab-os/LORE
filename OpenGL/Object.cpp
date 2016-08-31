#include "stdafx.h"
#include "Object.h"

#include <iostream>

#include "ObjectManager.h"
#include "ModelManager.h"

using namespace std;
using namespace glm;

Object::Object():	m__renderModel(),
					m__childs()
{



}


Object::~Object()
{

	delete(m__renderModel);

	for (auto const &child : m__childs) {

		delete(child);

	}

}


void Object::load()
{

	m__renderModel->load();

	for (auto const &child : m__childs) {

		cout << "[Object] for m__childs" << endl;
		child->load();

	}

}


void Object::render(mat4 &projection, mat4 &view, mat4 &model)
{

	m__renderModel->render(projection, view, model);

	for (auto const &child : m__childs) {

		child->render(projection, view, model);

	}

}


void Object::setRenderModel(string name)
{

	Model* model = ModelManager::get("Models/" + name);
	m__renderModel = new ModelRender((ModelRender*) model);

}


void Object::setRenderModel(Model* model)
{

	m__renderModel = (ModelRender*)model;

}


Object* Object::addObject(std::string path)
{

	Object* obj = ObjectManager::get(path);

	m__childs.push_back(obj);

	return obj;

}


vector<Object*> Object::getObjects()
{

	return m__childs;

}