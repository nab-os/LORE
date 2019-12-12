#pragma once

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LORE {
    class Light {
        public:
            Light();
            virtual ~Light();

            static glm::vec3 lightPosition;
    };
}
