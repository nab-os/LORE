#include "stdafx.h"
#include "Object.h"

#include <iostream>

#include "ObjectManager.h"

using namespace std;
using namespace glm;

Object::Object():	m__renderModel(),
					m__childs(),
					m__position()
{

	cout << "[Object] constructor" << endl;
	
}


Object::~Object()
{

	cout << "[Object] destructor" << endl;

	if (m__renderModel)
		delete m__renderModel;

	for (auto const &child : m__childs) {

		delete child;

	}

}


void Object::load()
{

	if (m__renderModel)
		m__renderModel->load();

	for (auto const &child : m__childs) {

		cout << "[Object] for m__childs" << endl;
		child->load();

	}

}


void Object::render(mat4 &projection, mat4 &view, mat4 &model)
{

	model = translate(model, m__position);

	if(m__renderModel)
		m__renderModel->render(projection, view, model);

	for (auto const &child : m__childs) {

		child->render(projection, view, model);

	}

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


void Object::addObject(Object* obj)
{

	m__childs.push_back(obj);

}


vector<Object*> Object::getObjects()
{

	return m__childs;

}