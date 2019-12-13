#pragma once

#include <vector>

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Light.h"
#include "Material.h"
#include "Node.h"
#include "Mesh.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

using std::vector;

namespace LORE {
    class Mesh {
        public:
            Mesh();
            ~Mesh();

            void load();

            void setMaterial(Material* mat) { m__material = mat; };

            void render(Node* renderer, glm::mat4 projection, glm::mat4 view, glm::mat4 model, GLuint environmentMapID = 0);

            Material* getMaterial() { return m__material; };

            void setIndices(vector<unsigned int> indices) { m__indices = indices; };
            vector<unsigned int> getIndices() { return m__indices; };

            void setVertices(vector<float> vertices) { m__vertices = vertices; };
            vector<float> getVertices() { return m__vertices; };

            void setUVs(vector<float> uvs) { m__UVs = uvs; };
            vector<float> getUVs() { return m__UVs; };

            void setNormals(vector<float> normals) { m__normals = normals; };
            vector<float> getNormals() { return m__normals; };

            void setTangents(vector<float> tangents) { m__tangents = tangents; };
            vector<float> getTangents() { return m__tangents; };

            void setColors(vector<float> colors) { m__colors = colors; };
            vector<float> getColors() { return m__colors; };

            void setIndexed(bool indexed) { m__indexed = indexed; };
            bool getIndexed() { return m__indexed; };

            void setMode(int mode) { m__mode = mode; };
            int getMode() { return m__mode; };

            void setPolyMode(int mode) { m__polyMode = mode; };
            int getPolyMode() { return m__polyMode; };

            void computeBitangents();
            void computeTangentBasis();

        private :
            GLuint m__VAO;
            GLuint m__elementBuffer;
            GLuint m__vertexBuffer;
            GLuint m__UVBuffer;
            GLuint m__normalBuffer;
            GLuint m__tangentBuffer;
            GLuint m__bitangentBuffer;
            GLuint m__colorBuffer;

            vector<float> m__UVs;
            vector<float> m__normals;
            vector<float> m__tangents;
            vector<float> m__bitangents;
            vector<float> m__colors;

            Material* m__material;

            vector<unsigned int> m__indices;
            vector<float> m__vertices;

            bool m__indexed;
            int m__mode;
            int m__polyMode;
    };
}
