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

    vector<float> vertices = 
    { 0,0,0,  -1,0,0,  1,0,0,
      -1,-1,0, 1,-1,0,  0,10,0, 
      -1,10,0,  1,10,0,  1,9,0, 0,9,0};
    setVertices(vertices);
    
    vector<unsigned int> indices = 
    { 2,3,4,1,5,6,1,3,2,5,0,1};
    setIndices(indices);

    setIndexed(true);
    setMode(GL_TRIANGLES);

}


Cube::~Cube()
{

	cout << this << " [Cube] destructor" << endl;

}
