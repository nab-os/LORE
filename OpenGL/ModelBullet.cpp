#include "ModelBullet.h"

ModelBullet::ModelBullet()
{



}


ModelBullet::~ModelBullet()
{



}


void ModelBullet::load(btDiscreteDynamicsWorld* world)
{

	m__fallShape = new btSphereShape(1);

	//m__fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 20, 0)));

	/*btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	m__fallShape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, m__fallMotionState, m__fallShape, fallInertia);
	m__fallRigidBody = new btRigidBody(fallRigidBodyCI);
	world->addRigidBody(m__fallRigidBody);*/

}

glm::vec3 ModelBullet::getPosition()
{

	btTransform trans;
	m__fallRigidBody->getMotionState()->getWorldTransform(trans);

	return glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

}
