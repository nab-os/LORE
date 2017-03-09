#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "Mesh.h"

#ifndef BUFFER_OFFSET

#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

namespace LORE
{

    class Mesh
    {

        public:

            Mesh();
            ~Mesh();

            void load();

            void setMaterial(Material* mat) { m__material = mat; };

            void render(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model, GLuint environmentMapID = 0);

            GLuint& getVAO();
            GLuint& getVBO();

            Material* getMaterial() { return m__material;  };

            int getVertexCount();
            int getVerticesSize();
            void setVertices(std::vector<glm::vec3> vertices) { m__vertices = vertices; };
            std::vector<glm::vec3> getVertices();
            float* getVerticesFloat();

            void setUVs(std::vector<glm::vec2> uvs) { m__UVs = uvs; };
            int getUVCount();
            int getUVsSize();
            std::vector<glm::vec2> getUVs();
            float* getUVsFloat();

            void setNormals(std::vector<glm::vec3> normals) { m__normals = normals; };
            int getNormalCount();
            int getNormalsSize();
            std::vector<glm::vec3> getNormals();
            float* getNormalsFloat();

            void computeTangentBasis(
                    // inputs
                    std::vector<glm::vec3> & vertices,
                    std::vector<glm::vec2> & uvs,
                    std::vector<glm::vec3> & normals,

                    // outputs
                    std::vector<glm::vec3> & tangents,
                    std::vector<glm::vec3> & bitangents);

        private :

            GLuint m__VAO;
            GLuint m__VBO;

            std::vector<glm::vec2> m__UVs;
            std::vector<glm::vec3> m__normals;

            Material* m__material;

            std::vector<glm::vec3> m__vertices;

            static float* vec3ToFloat(std::vector<glm::vec3>);

    };

}

#endif
