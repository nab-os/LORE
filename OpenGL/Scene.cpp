#include "stdafx.h"
#include "Scene.h"

#include <iostream>

using namespace std;
using namespace glm;

Scene::Scene(int width, int height):	Object(), 
										m__width(width),
										m__height(height),
										m__paused(false),
										m__projection(mat4(1.0)),
										m__view(mat4(1.0)),
										m__model(mat4(1.0)),
										m__cam(),
										m__lights()
{

	cout << "[Scene] constructor" << endl;

}


Scene::~Scene()
{

	cout << "[ModelRender] destructor" << endl;

	if(m__cam)
		delete m__cam;
	
}


void Scene::load()
{

	cout << "[Scene] init" << endl;

	Object::load();

	m__projection = perspective(70.0, (double)m__width / m__height, 0.1, 500.0);
	m__model = mat4(1.0);

	m__cam = new Camera(vec3(3.5, 3, 4), vec3(0, 0, 0), vec3(0, 1, 0), 0.1f, 0.5f);

}


void Scene::render()
{

	if (!m__paused)
	{
	
		//m__cam->deplacer();
		m__cam->lookAt(m__view);
	
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glViewport(0, 0, m__width, m__height);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->renderObjects();

}


void Scene::renderObjects()
{

	mat4 saveModel = m__model;

	Object::render(m__projection, m__model, m__view);

	m__model = saveModel;

}


void Scene::renderLights()
{

	

}
