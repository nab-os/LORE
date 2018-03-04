#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Node.h"
#include "Mesh.h"
#include "Material.h"

namespace LORE
{

    class Object: public Node
    {

        public:

            Object();
            ~Object();

            void load();
            void render(Node* renderer, glm::mat4 projection, glm::mat4 view, glm::mat4 model, GLuint environmentMapID = 0);

            virtual bool isEmpty() { return false; };
            virtual bool isObject() { return true; };
            virtual bool isCamera() { return false; };

            void setMesh(Mesh* mesh);

            Mesh* getMesh() { return m__mesh; };

        private:

            Mesh* m__mesh;

    };

}

#endif
