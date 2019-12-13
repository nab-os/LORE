#pragma once

#include <vector>

#include "Mesh.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

using std::vector;

namespace LORE {
    class MeshRender: public Mesh {
        public:
            explicit MeshRender();
            explicit MeshRender(const MeshRender*);
            ~MeshRender();

            void computeTangentBasis(
                    // inputs
                    vector<glm::vec3> & vertices,
                    vector<glm::vec2> & uvs,
                    vector<glm::vec3> & normals,

                    // outputs
                    vector<glm::vec3> & tangents,
                    vector<glm::vec3> & bitangents);

            void load();
            void render(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model, GLuint environmentMapID = 0);

            GLuint& getVAO();
            GLuint& getVBO();

            void setUVs(vector<glm::vec2> uvs) { m__UVs = uvs; };
            int getUVCount();
            int getUVsSize();
            vector<glm::vec2> getUVs();
            float* getUVsFloat();

            void setNormals(vector<glm::vec3> normals) { m__normals = normals; };
            int getNormalCount();
            int getNormalsSize();
            vector<glm::vec3> getNormals();
            float* getNormalsFloat();

        private :
            GLuint m__VAO;
            GLuint m__VBO;

            vector<glm::vec2> m__UVs;
            vector<glm::vec3> m__normals;
    };
}
