#include "Object.h"

#include <iostream>

using namespace std;
using namespace glm;
using namespace LORE;

Object::Object():   m__mesh()
{

	cout << this << " [Object] constructor" << endl;

}


Object::~Object()
{

	cout << this << " [Object] destructor" << endl;

	if (m__mesh)
		delete m__mesh;

}


void Object::load()
{

    cout << this << " [Object] load" << endl;

	if (m__mesh)
		m__mesh->load();

    Node::load();

}


void Object::render(mat4 &projection, mat4 &view, mat4 &model, GLuint environmentMapID)
{

    //cout << this << "[Object] render" << endl;

    mat4 save = model;

    //glm::vec3 pos = m__positionProxy;
	//glm::vec3 scale = m__scaleProxy;
	//glm::vec3 rot = vec3(0, 0, 0);

	//model = glm::scale(model, scale);
	//model = glm::translate(model, pos);
	//model = glm::rotate(model, );

	if(m__mesh)
		m__mesh->render(projection, view, model, environmentMapID);

    Node::render(projection, view, model, environmentMapID);

    model = save;

}


void Object::setMesh(Mesh* mesh)
{

    if(!mesh)
        cout << "Warning !!! Setting NULL Mesh !!!" << endl;
    m__mesh = mesh;

}
