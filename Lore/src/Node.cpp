#include "Node.h"

#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using glm::vec3;
using glm::mat4;

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
    mat4 local_model = getModel(model);

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

void Node::move(vec3 offset) {
    m__position += offset;
}

void Node::setPosition(vec3 pos) {
    m__position = pos;
}

void Node::setPosition(float x, float y, float z) {
    m__position = vec3(x, y, z);
}

vec3 Node::getPosition() {
    return m__position;
}

void Node::setScale(vec3 scale) {
    m__scale = scale;
}

mat4 Node::getModel(mat4 model) {
    mat4 scaled = scale(model, m__scale);
    mat4 rotated = mat4_cast(m__rotation) * scaled;
	return translate(model, m__position) * rotated;
}
