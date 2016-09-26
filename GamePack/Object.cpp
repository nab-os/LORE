#include "Object.h"

#include <iostream>

#include "ObjectManager.h"

using namespace std;
using namespace glm;

Object::Object():	m__renderModel(),
					m__bulletModel(),
					m__childs()
{

	cout << "[Object] constructor" << endl;

}


Object::~Object()
{

	cout << "[Object] destructor" << endl;

	if (m__renderModel)
		delete m__renderModel;

	if (m__bulletModel)
		delete m__bulletModel;

	for (auto const &child : m__childs) {

		delete child;

	}

}


void Object::load(btDiscreteDynamicsWorld* world)
{

	if (m__renderModel)
		m__renderModel->load();

	/*if (world && m__bulletModel)
		m__bulletModel->load(world);*/

	for (auto const &child : m__childs) {

		cout << "[Object] for m__childs" << endl;
		child->load(world);

	}

}


void Object::render(mat4 &projection, mat4 &view, mat4 &model)
{

	glm::vec3 pos = vec3(0, 0, 0);

	if (m__bulletModel)
		pos = m__bulletModel->getPosition();

	model = glm::translate(model, pos);

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


void Object::setBulletModel(Model* model)
{

	m__bulletModel = (ModelBullet*)model;

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
