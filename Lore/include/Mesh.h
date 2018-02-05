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

            void render(glm::mat4 projection, glm::mat4 view, glm::mat4 model, GLuint environmentMapID = 0);

            Material* getMaterial() { return m__material;  };

            void setIndices(std::vector<unsigned int> indices) { m__indices = indices; };
            std::vector<unsigned int> getIndices() { return m__indices; };

            void setVertices(std::vector<float> vertices) { m__vertices = vertices; };
            std::vector<float> getVertices() { return m__vertices; };

            void setUVs(std::vector<float> uvs) { m__UVs = uvs; };
            std::vector<float> getUVs() { return m__UVs; };

            void setNormals(std::vector<float> normals) { m__normals = normals; };
            std::vector<float> getNormals() { return m__normals; };

            void setColors(std::vector<float> colors) { m__colors = colors; };
            std::vector<float> getColors() { return m__colors; };

            void setIndexed(bool indexed) { m__indexed = indexed; };
            bool getIndexed() { return m__indexed; };

            void setMode(int mode) { m__mode = mode; };
            int getMode() { return m__mode; };

/*            void computeTangentBasis(
                    // inputs
                    std::vector<glm::vec3> & vertices,
                    std::vector<glm::vec2> & uvs,
                    std::vector<glm::vec3> & normals,

                    // outputs
                    std::vector<glm::vec3> & tangents,
                    std::vector<glm::vec3> & bitangents);
                    */

        private :

            GLuint m__VAO;
            GLuint m__elementBuffer;
            GLuint m__vertexBuffer;
            GLuint m__UVBuffer;
            GLuint m__normalBuffer;
            GLuint m__colorBuffer;

            std::vector<float> m__UVs;
            std::vector<float> m__normals;
            std::vector<float> m__colors;

            Material* m__material;

            std::vector<unsigned int> m__indices;
            std::vector<float> m__vertices;

            bool m__indexed;
            int m__mode;
    };
}

#endif
