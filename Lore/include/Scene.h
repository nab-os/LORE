#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Node.h"

#include "Light.h"
#include "CubeMap.h"

namespace LORE
{
    
    class Scene: public Node
    {

        public:

            Scene();
            virtual ~Scene();

            bool getPaused(){ return m__paused; };

        private:

            bool m__paused;

            CubeMap* m__environmentMap;
            std::vector<Light*> m__lights;

            void renderLights();

    };

}

#endif
