#include "Object.h"

#include <iostream>

#include "ObjectManager.h"

using namespace std;
using namespace glm;

Object::Object():   m__renderModel(),
					m__bulletModel(),
					m__childs(),
					m__positionProxy(),
					m__scaleProxy(vec3(1.0)),
					m__physicsEnabled(true)
{

	cout << this << " [Object] constructor" << endl;

}


Object::~Object()
{

	cout << this << " [Object] destructor" << endl;

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

    cout << this << " [Object] load" << endl;

	if (m__renderModel)
		m__renderModel->load();

	if (world && m__bulletModel)
		m__bulletModel->load(world);

	for (auto const &child : m__childs) {

		child->load(world);

	}

}


void Object::render(mat4 &projection, mat4 &view, mat4 &model, GLuint environmentMapID)
{

    mat4 save = model;

	glm::vec3 pos = m__positionProxy;
	glm::vec3 scale = m__scaleProxy;
	//glm::vec3 rot = vec3(0, 0, 0);

	if (m__bulletModel && m__physicsEnabled)
    {
		pos = m__bulletModel->getPosition();
		//rot = m__bulletModel->getRotation();
    }

	//model = glm::scale(model, scale);
	model = glm::translate(model, pos);
	//model = glm::rotate(model, );

	if(m__renderModel)
		m__renderModel->render(projection, view, model, environmentMapID);

	for (auto const &child : m__childs) {

		child->render(projection, view, model, environmentMapID);

	}

    model = save;

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

//	Object* obj = ObjectManager::get(path);

//	m__childs.push_back(obj);

//	return obj;
return nullptr;
}


void Object::addObject(Object* obj)
{

	m__childs.push_back(obj);

}


vector<Object*> Object::getObjects()
{

	return m__childs;

}

void Object::applyForce(glm::vec3 pos)
{

    if(m__bulletModel)
        m__bulletModel->applyForce(pos);

}


void Object::setLinearVelocity(glm::vec3 vec)
{

    if(m__bulletModel)
        m__bulletModel->setLinearVelocity(vec);

}


void Object::move(glm::vec3 pos)
{

    if(m__bulletModel)
        m__bulletModel->move(pos);

}


void Object::setPosition(glm::vec3 pos)
{

    if(m__bulletModel)
        m__bulletModel->setPosition(pos);

    m__positionProxy = pos;

}


glm::vec3 Object::getPosition()
{

    if(m__bulletModel && m__physicsEnabled)
    {
        m__positionProxy = m__bulletModel->getPosition();
    }

    return m__positionProxy;

}


void Object::setScale(glm::vec3 scale)
{

    m__scaleProxy = scale;

}


void Object::forcePhysics()
{

	if(m__bulletModel)
        m__bulletModel->forcePhysics();

    m__physicsEnabled = true;

    for (auto const &child : m__childs) {

		child->forcePhysics();

	}

}


void Object::disablePhysics()
{

	if(m__bulletModel)
        m__bulletModel->disablePhysics();

    m__physicsEnabled = false;

    for (auto const &child : m__childs) {

		child->disablePhysics();

	}

}


