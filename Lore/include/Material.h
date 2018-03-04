#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include "Texture.h"

namespace LORE
{

    class Material
    {

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

        private:

            Shader* m__shader;

            glm::vec4 m__diffuseColor;
            float m__metallness;
            float m__roughness;

            Texture* m__pbrTexture;
            Texture* m__diffuseTexture;
            Texture* m__normalTexture;
            Texture* m__occlusionTexture;

            bool m__culling;

    };

}

#endif
