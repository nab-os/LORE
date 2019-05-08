#include "Diamond.h"

#include <iostream>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;
using namespace LORE;

Diamond::Diamond(int n): Mesh()
{

	cout << this << " [Diamond] constructor" << endl;

    vector<float> vertices;
    vector<float> normals;

    float step = 2*M_PI / n;
    //Layer2
    for(int i = 0; i < n; i++)
    {
        float angle = i * step;

        //Top
        vertices.push_back(0);
        vertices.push_back(1);
        vertices.push_back(0);

        vertices.push_back(0.5*sin(angle));
        vertices.push_back(1);
        vertices.push_back(0.5*cos(angle));
        
        vertices.push_back(0.5*sin(angle + step));
        vertices.push_back(1);
        vertices.push_back(0.5*cos(angle + step));

        //First angles
        vertices.push_back(0.5*sin(angle));
        vertices.push_back(1);
        vertices.push_back(0.5*cos(angle));

        vertices.push_back(0.75*sin(angle + step/2.0));
        vertices.push_back(0.75);
        vertices.push_back(0.75*cos(angle + step/2.0));

        vertices.push_back(0.5*sin(angle + step));
        vertices.push_back(1);
        vertices.push_back(0.5*cos(angle + step));

        //Second angles
        vertices.push_back(0.5*sin(angle));
        vertices.push_back(1);
        vertices.push_back(0.5*cos(angle));

        vertices.push_back(0.75*sin(angle - step/2.0));
        vertices.push_back(0.75);
        vertices.push_back(0.75*cos(angle - step/2.0));

        vertices.push_back(0.75*sin(angle + step/2.0));
        vertices.push_back(0.75);
        vertices.push_back(0.75*cos(angle + step/2.0));
        
        //Bottom angles
        vertices.push_back(0.75*sin(angle - step/2.0));
        vertices.push_back(0.75);
        vertices.push_back(0.75*cos(angle - step/2.0));

        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);

        vertices.push_back(0.75*sin(angle + step/2.0));
        vertices.push_back(0.75);
        vertices.push_back(0.75*cos(angle + step/2.0));
    }

    for(int i = 0; i < n * 4; i++)
    {

        int i1 = i * 9; 
        int i2 = i1 + 3; 
        int i3 = i2 + 3; 
        vec3 v1 = vec3(vertices[i1], vertices[i1+1], vertices[i1+2]);
        vec3 v2 = vec3(vertices[i2], vertices[i2+1], vertices[i2+2]);
        vec3 v3 = vec3(vertices[i3], vertices[i3+1], vertices[i3+2]);
        vec3 normal = normalize(cross(v2-v1, v3-v1));

        normals.push_back(normal.x);
        normals.push_back(normal.y);
        normals.push_back(normal.z);
        normals.push_back(normal.x);
        normals.push_back(normal.y);
        normals.push_back(normal.z);
        normals.push_back(normal.x);
        normals.push_back(normal.y);
        normals.push_back(normal.z);
    
    }
 
    setVertices(vertices);
    setNormals(normals);

    setMode(GL_TRIANGLES);
    //setPolyMode(GL_LINE);
}


Diamond::~Diamond()
{

	cout << this << " [Diamond] destructor" << endl;

}
