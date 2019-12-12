#include "Node.h"

#include <iostream>

using namespace std;
using namespace glm;
using namespace LORE;

Node::Node(): m__childs(),
              m__position(0.0),
              m__rotation(),
              m__scale(1.0) {
	cout << this << " [Node] constructor" << endl;
}

Node::~Node() {
	cout << this << " [Node] destructor" << endl;
}

void Node::render(Node* renderer, mat4 projection, mat4 view, mat4 model, GLuint environmentMapID) {
    //cout << this << " [Node] render" << endl;
    glm::mat4 local_model = getModel(model);

	for (auto const &child : m__childs) {
		child->render(renderer, projection, view, local_model);
	}
}

void Node::addChild(Node* obj) {
	m__childs.push_back(obj);
}

vector<Node*> Node::getChilds() {
	return m__childs;
}

void Node::move(glm::vec3 pos) {
    m__position += pos;
}

void Node::setPosition(glm::vec3 pos) {
    m__position = pos;
}

void Node::setPosition(float x, float y, float z) {
    m__position = vec3(x, y, z);
}

glm::vec3 Node::getPosition() {
    return m__position;
}

void Node::setScale(glm::vec3 scale) {
    m__scale = scale;
}

glm::mat4 Node::getModel(glm::mat4 model) {
    mat4 scaled = glm::scale(model, m__scale);
    mat4 rotated = glm::mat4_cast(m__rotation) * scaled;
	return glm::translate(model, m__position) * rotated;
}
