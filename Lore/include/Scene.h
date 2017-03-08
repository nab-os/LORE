#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.h"

#include "Light.h"
#include "CubeMap.h"

namespace LORE
{

    class Scene: public Object
    {

        public:

            Scene(int width = 1920, int height = 1080);
            virtual ~Scene();

            void load();

            void render(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model);

            bool getPaused(){ return m__paused; };

        private:

            bool m__paused;

            CubeMap* m__environmentMap;
            std::vector<Light*> m__lights;

            void renderObjects(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model);
            void renderLights();

    };

}

#endif
