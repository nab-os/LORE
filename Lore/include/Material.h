#pragma once

#include <map>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"

namespace LORE {
    class Material {
        public:
            Material();
            virtual ~Material();

            void load();

            Shader* getShader() { return m__shader; };
            void setShader(Shader* shader) { m__shader = shader; };

            glm::vec4 getDiffuseColor() { return m__diffuseColor; };
            void setDiffuseColor(glm::vec4 color) { m__diffuseColor = color; };

            float getMetallness() { return m__metallness; };
            void setMetallness(float metallness) { m__metallness = metallness; };

            float getRoughness() { return m__roughness; };
            void setRoughness(float roughness) { m__roughness = roughness; };

            Texture* getPbrTexture() { return m__pbrTexture; };
            void setPbrTexture(Texture* texture) { m__pbrTexture = texture; };

            Texture* getDiffuseTexture() { return m__diffuseTexture; };
            void setDiffuseTexture(Texture* texture) { m__diffuseTexture = texture; };

            Texture* getNormalTexture() { return m__normalTexture; };
            void setNormalTexture(Texture* texture) { m__normalTexture = texture; };

            Texture* getOcclusionTexture() { return m__occlusionTexture; };
            void setOcclusionTexture(Texture* texture) { m__occlusionTexture = texture; };

            bool getCulling() { return m__culling; };
            void setCulling(bool culling) { m__culling = culling; };

            void addCustomIntUniform(std::string name, int* value);
            void addCustomFloatUniform(std::string name, float* value);
            void addCustomVec2Uniform(std::string name, glm::vec2* value);
            void addCustomVec3Uniform(std::string name, glm::vec3* value);

            void sendCustomUniforms();
            void sendTextures();

        private:
            Shader* m__shader;

            glm::vec4 m__diffuseColor;
            float m__metallness;
            float m__roughness;

            std::map<std::string, int*> m__customIntUniforms;
            std::map<std::string, float*> m__customFloatUniforms;
            std::map<std::string, glm::vec2*> m__customVec2Uniforms;
            std::map<std::string, glm::vec3*> m__customVec3Uniforms;

            Texture* m__pbrTexture;
            Texture* m__diffuseTexture;
            Texture* m__normalTexture;
            Texture* m__occlusionTexture;

            std::map<std::string, std::pair<GLuint, GLuint>> m__textures;

            bool m__culling;
    };
}
