#include "Node.h"

#include <iostream>

using namespace std;
using namespace glm;
using namespace LORE;

Node::Node(): m__childs(),
              m__position(),
              m__scale()
{

	cout << this << " [Node] constructor" << endl;

}


Node::~Node()
{

	cout << this << " [Node] destructor" << endl;

    for (auto const &child : m__childs) {

		delete child;

	}

}


void Node::render(mat4 &projection, mat4 &view, mat4 &model, GLuint environmentMapID)
{

    //cout << this << "[Node] render" << endl;

    mat4 save = model;

    //glm::vec3 pos = m__position;
	//glm::vec3 scale = m__scale;
	//glm::vec3 rot = vec3(0, 0, 0);

	//model = glm::scale(model, scale);
	//model = glm::translate(model, pos);
	//model = glm::rotate(model, );

	for (auto const &child : m__childs) {

		child->render(projection, view, model, environmentMapID);

	}

    model = save;

}


void Node::addChild(Node* obj)
{

	m__childs.push_back(obj);

}


vector<Node*> Node::getChilds()
{

	return m__childs;

}


void Node::move(glm::vec3 pos)
{
    m__position += pos;
}


void Node::setPosition(glm::vec3 pos)
{
    m__position = pos;
}


void Node::setPosition(float x, float y, float z)
{
    m__position = vec3(x, y, z);
}


glm::vec3 Node::getPosition()
{
    return m__position;
}


void Node::setScale(glm::vec3 scale)
{
    m__scale = scale;
}

