#include "Object.h"

#include <iostream>

using namespace std;
using namespace glm;
using namespace LORE;

Object::Object():   m__mesh(),
					m__childs(),
					m__positionProxy(),
					m__scaleProxy(vec3(1.0))
{

	cout << this << " [Object] constructor" << endl;

}


Object::~Object()
{

	cout << this << " [Object] destructor" << endl;

	if (m__mesh)
		delete m__mesh;

    for (auto const &child : m__childs) {

		delete child;

	}

}


void Object::load()
{

    cout << this << " [Object] load" << endl;

	if (m__mesh)
		m__mesh->load();

	for (auto const &child : m__childs) {

		child->load();

	}

}


void Object::render(mat4 &projection, mat4 &view, mat4 &model, GLuint environmentMapID)
{

    mat4 save = model;

	glm::vec3 pos = m__positionProxy;
	glm::vec3 scale = m__scaleProxy;
	//glm::vec3 rot = vec3(0, 0, 0);

	//model = glm::scale(model, scale);
	//model = glm::translate(model, pos);
	//model = glm::rotate(model, );

	if(m__mesh)
		m__mesh->render(projection, view, model, environmentMapID);

	for (auto const &child : m__childs) {

		child->render(projection, view, model, environmentMapID);

	}

    model = save;

}


void Object::setMesh(Mesh* mesh)
{

	m__mesh = mesh;

}


void Object::addObject(Object* obj)
{

	m__childs.push_back(obj);

}


vector<Object*> Object::getObjects()
{

	return m__childs;

}


void Object::move(glm::vec3 pos)
{

    m__positionProxy += pos;

}


void Object::setPosition(glm::vec3 pos)
{

    m__positionProxy = pos;

}


glm::vec3 Object::getPosition()
{

    return m__positionProxy;

}


void Object::setScale(glm::vec3 scale)
{

    m__scaleProxy = scale;

}

