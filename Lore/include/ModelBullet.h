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
		~ModelBullet();

		void load(btDiscreteDynamicsWorld* world);

		void applyForce(glm::vec3 pos);
		void setLinearVelocity(glm::vec3 vec);
        void move(glm::vec3 pos);
        void setPosition(glm::vec3 pos);
		glm::vec3 getPosition();

		void forcePhysics();		
		void disablePhysics();		

        btRigidBody* getRigidBody(){ return m__fallRigidBody; };


	private:

		btCollisionShape* m__fallShape;
		btDefaultMotionState* m__fallMotionState;
		btRigidBody* m__fallRigidBody;

		bool m__active;

};

