#pragma once

#include <vector>

#include <btBulletDynamicsCommon.h>

#include "Model.h"


#ifndef BUFFER_OFFSET

	#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

class ModelBullet : public Model
{

	public:

		ModelBullet();
		virtual ~ModelBullet();

		void load(btDiscreteDynamicsWorld* world);

		glm::vec3 getPosition();

	private:

		btCollisionShape* m__fallShape;
		btDefaultMotionState* m__fallMotionState;
		btRigidBody* m__fallRigidBody;

};

