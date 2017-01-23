#include "ModelBullet.h"

#include <iostream>

using namespace std;
using namespace LORE;

ModelBullet::ModelBullet(): m__active(true)
{

    cout << this << " [ModelBullet] Constructor" << endl;

}


ModelBullet::~ModelBullet()
{

	if(m__fallShape)
		delete m__fallShape;
	if(m__fallRigidBody)
		delete m__fallRigidBody;
	if(m__fallMotionState)
		delete m__fallMotionState;

}


void ModelBullet::load(btDiscreteDynamicsWorld* world)
{

    cout << this << " [ModelBullet] load" << endl;

	m__fallShape = new btBoxShape(btVector3(1, 1, 1));

	m__fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0)));

	btScalar mass = 0.1;
	btVector3 fallInertia(0, 0, 0);
	m__fallShape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, m__fallMotionState, m__fallShape, fallInertia);
	m__fallRigidBody = new btRigidBody(fallRigidBodyCI);
	world->addRigidBody(m__fallRigidBody);

}


void ModelBullet::applyForce(glm::vec3 pos)
{

    btVector3 a(pos.x, pos.y, pos.z);
    btVector3 b(0, 0, 0);

	m__fallRigidBody->applyForce(a, b);

}


void ModelBullet::setPosition(glm::vec3 pos)
{

	btTransform initialTransform;

    btVector3 a(pos.x, pos.y, pos.z);
    btQuaternion b(0, 0, 0, 1);

	initialTransform.setOrigin(a);
	initialTransform.setRotation(b);

	m__fallRigidBody->getMotionState()->setWorldTransform(initialTransform);

}


void ModelBullet::setLinearVelocity(glm::vec3 vec)
{

    btVector3 a(vec.x, vec.y, vec.z);

	m__fallRigidBody->setLinearVelocity(a);

}


void ModelBullet::move(glm::vec3 pos)
{

	btTransform trans;
	m__fallRigidBody->getMotionState()->getWorldTransform(trans);

	glm::vec3 last_pos(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	btTransform initialTransform;

    btVector3 a(last_pos.x + pos.x, last_pos.y + pos.y, last_pos.z + pos.z);
    btQuaternion b(0, 0, 0, 1);

	initialTransform.setOrigin(a);
	initialTransform.setRotation(b);

	m__fallRigidBody->getMotionState()->setWorldTransform(initialTransform);

}


glm::vec3 ModelBullet::getPosition()
{

	btTransform trans;
	m__fallRigidBody->getMotionState()->getWorldTransform(trans);

	return glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

}


void ModelBullet::forcePhysics()
{

	m__fallRigidBody->forceActivationState(DISABLE_DEACTIVATION);
	m__fallRigidBody->activate();

}


void ModelBullet::disablePhysics()
{

	m__fallRigidBody->forceActivationState(DISABLE_SIMULATION);

}
