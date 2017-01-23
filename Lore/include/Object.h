#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <bullet/btBulletDynamicsCommon.h>

//#include "ModelBullet.h"
#include "ModelRender.h"
#include "Material.h"

namespace LORE
{

    class Object
    {

        public:

            Object();
            ~Object();

            void load(/*btDiscreteDynamicsWorld* world = nullptr*/);
            void render(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model, GLuint environmentMapID = 0);

            void setRenderModel(Model* model);
            //void setBulletModel(Model* model);

            Object* addObject(std::string path = "default");
            void addObject(Object* obj);
            std::vector<Object*> getObjects();

            //void applyForce(glm::vec3 pos);
            //void setLinearVelocity(glm::vec3 vec);
            void move(glm::vec3 pos);
            void setPosition(glm::vec3 pos);
            glm::vec3 getPosition();
            void setScale(glm::vec3 scale);

            //void forcePhysics();
            //void disablePhysics();

            //ModelBullet* getModelBullet() { return m__bulletModel; };
            ModelRender* getModelRender() { return m__renderModel; };

        private:

            ModelRender* m__renderModel;
            //ModelBullet* m__bulletModel;

            std::vector<Object*> m__childs;

            glm::vec3 m__positionProxy;
            glm::vec3 m__scaleProxy;
            bool m__physicsEnabled;

    };

}

#endif
