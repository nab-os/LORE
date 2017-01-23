#include "Scene.h"

#include <iostream>

#include "Camera.h"

using namespace std;
using namespace glm;
using namespace LORE;

Scene::Scene(int width, int height):	Object(),
										m__paused(false),
//										m__broadphase(),
//										m__collisionConfiguration(),
//										m__dispatcher(),
//                                      m__solver(),
//										m__dynamicsWorld(),
										m__environmentMap(),
										m__lights()
{

	cout << this << " [Scene] constructor" << endl;

}


Scene::~Scene()
{

	cout << this << " [ModelRender] destructor" << endl;

/*	if(m__dynamicsWorld)
		delete m__dynamicsWorld;
	if(m__solver)
		delete m__solver;
	if(m__dispatcher)
		delete m__dispatcher;
	if(m__collisionConfiguration)
		delete m__collisionConfiguration;
	if(m__broadphase)
		delete m__broadphase;
	if(m__groundShape)
		delete m__groundShape;
	if(m__groundMotionState)
		delete m__groundMotionState;
	if(m__groundMotionState)
		delete m__groundMotionState;
*/	if(m__environmentMap)
		delete m__environmentMap;

}


void Scene::load()
{

	cout << this << " [Scene] load" << endl;

/*	m__broadphase = new btDbvtBroadphase();
	m__collisionConfiguration = new btDefaultCollisionConfiguration();
	m__dispatcher = new btCollisionDispatcher(m__collisionConfiguration);
	m__solver = new btSequentialImpulseConstraintSolver;
	m__dynamicsWorld = new btDiscreteDynamicsWorld(m__dispatcher, m__broadphase, m__solver, m__collisionConfiguration);
	m__dynamicsWorld->setGravity(btVector3(0, btScalar(-9.81), 0));

	m__groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	m__groundMotionState =	new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -5, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, m__groundMotionState, m__groundShape, btVector3(0, 0, 0));
	m__groundRigidBody = new btRigidBody(groundRigidBodyCI);

	m__dynamicsWorld->addRigidBody(m__groundRigidBody);
*/
	m__environmentMap = new CubeMap();
	m__environmentMap->load();

    Object::load(/*m__dynamicsWorld*/);

}

/*
void Scene::step(int fps)
{

    m__dynamicsWorld->stepSimulation(1 / float(fps), 10);

}*/


void Scene::render(mat4 &projection, mat4 &view, mat4 &model)
{

	this->renderObjects(projection, view, model);

}


void Scene::renderObjects(mat4 &projection, mat4 &view, mat4 &model)
{

	mat4 saveModel = model;

	Object::render(projection, view, model, m__environmentMap->getID());

	model = saveModel;

}


void Scene::renderLights()
{



}

/*
void Scene::addRigidBody(ModelBullet* model)
{

    m__dynamicsWorld->addRigidBody(model->getRigidBody());

}*/


