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

#include "Mesh.h"
#include "Material.h"

namespace LORE
{

    class Object
    {

        public:

            Object();
            ~Object();

            void load();
            void render(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model, GLuint environmentMapID = 0);

            void setMesh(Mesh* mesh);

            Object* addObject(std::string path = "default");
            void addObject(Object* obj);
            std::vector<Object*> getObjects();

            void move(glm::vec3 pos);
            void setPosition(glm::vec3 pos);
            glm::vec3 getPosition();
            void setScale(glm::vec3 scale);

            Mesh* getMesh() { return m__mesh; };

        private:

            Mesh* m__mesh;

            std::vector<Object*> m__childs;

            glm::vec3 m__positionProxy;
            glm::vec3 m__scaleProxy;

    };

}

#endif
