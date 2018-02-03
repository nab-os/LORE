#include "Cube.h"

#include <iostream>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;
using namespace LORE;

Cube::Cube(): Mesh()
{

	cout << this << " [Cube] constructor" << endl;

    vector<vec3> vertices;
    vertices.push_back(vec3(0, 0, 0));
    vertices.push_back(vec3(0, 1, 0));
    vertices.push_back(vec3(1, 0, 0));
    vertices.push_back(vec3(0, 1, 0));
    vertices.push_back(vec3(1, 1, 0));
    vertices.push_back(vec3(1, 0, 0));

    setVertices(vertices);

}


Cube::~Cube()
{

	cout << this << " [Cube] destructor" << endl;

}
