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
										/*m__dynamicsWorld(),
										m__solver(),
										m__dispatcher(),
										m__collisionConfiguration(),
										m__broadphase(),*/
										m__lights()
{

	cout << "[Scene] constructor" << endl;

}


Scene::~Scene()
{

	cout << "[ModelRender] destructor" << endl;

	if(m__cam)
		delete m__cam;

	/*delete m__dynamicsWorld;
	delete m__solver;
	delete m__dispatcher;
	delete m__collisionConfiguration;
	delete m__broadphase;*/

}


void Scene::load()
{

	cout << "[Scene] init" << endl;

	Object::load();

	m__projection = perspective(70.0, (double)m__width / m__height, 0.1, 500.0);
	m__model = mat4(1.0);

	m__cam = new Camera(vec3(3.5, 3, 4), vec3(0, 0, 0), vec3(0, 1, 0), 0.1f, 0.5f);

	/*m__broadphase = new btDbvtBroadphase();
	m__collisionConfiguration = new btDefaultCollisionConfiguration();
	m__dispatcher = new btCollisionDispatcher(m__collisionConfiguration);
	m__solver = new btSequentialImpulseConstraintSolver;
	m__dynamicsWorld = new btDiscreteDynamicsWorld(m__dispatcher, m__broadphase, m__solver, m__collisionConfiguration);
	m__dynamicsWorld->setGravity(btVector3(0, btScalar(-9.81), 0));

	m__groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	m__groundMotionState =	new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, m__groundMotionState, m__groundShape, btVector3(0, 0, 0));
	m__groundRigidBody = new btRigidBody(groundRigidBodyCI);

	m__dynamicsWorld->addRigidBody(m__groundRigidBody);*/

}


void Scene::step(int fps)
{

	//m__dynamicsWorld->stepSimulation(1 / float(fps), 10);

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
