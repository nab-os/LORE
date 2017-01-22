#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>

//#include <btBulletDynamicsCommon.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.h"

#include "Light.h"
//#include "ModelBullet.h"
#include "CubeMap.h"

class Scene: public Object
{

	public:

		Scene(int width = 1920, int height = 1080);
		virtual ~Scene();

		void load();

//		void step(int fps = 60);
		void render(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model);

        bool getPaused(){ return m__paused; };
//        btDiscreteDynamicsWorld* getWorld(){ return m__dynamicsWorld; };

//        void addRigidBody(ModelBullet* model);

	private:

		bool m__paused;

//		btBroadphaseInterface* m__broadphase;
//		btDefaultCollisionConfiguration* m__collisionConfiguration;
//		btCollisionDispatcher* m__dispatcher;
//		btSequentialImpulseConstraintSolver* m__solver;
//		btDiscreteDynamicsWorld* m__dynamicsWorld;

//		btCollisionShape* m__groundShape;
//		btDefaultMotionState* m__groundMotionState;
//		btRigidBody* m__groundRigidBody;

		CubeMap* m__environmentMap;
		std::vector<Light*> m__lights;

		void renderObjects(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model);
		void renderLights();

};

