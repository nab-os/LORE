#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LORE
{

    class Node
    {

        public:

            Node();
            virtual ~Node();

            virtual void load() {};
            virtual void render(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model, GLuint environmentMapID = 0);

            Node* addChild(std::string path = "default");
            void addChild(Node* obj);
            std::vector<Node*> getChilds();

            void move(glm::vec3 pos);
            void setPosition(glm::vec3 pos);
            void setPosition(float x, float y, float z);
            glm::vec3 getPosition();
            void setScale(glm::vec3 scale);

            virtual bool isEmpty() { return true; };
            virtual bool isObject() { return false; };
            virtual bool isCamera() { return false; };

        private:

            std::vector<Node*> m__childs;

            glm::vec3 m__position;
            glm::vec3 m__scale;

    };

}

#endif
