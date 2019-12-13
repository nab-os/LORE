#pragma once

#include <string>

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::string;

namespace LORE {
    class Shader {
        public:
            Shader(string shaderName = "default");
            virtual ~Shader();

            bool load();

            GLuint getProgramID();

            void sendMat4Uniform(string nom, glm::mat4 matrice);
            void sendMat3Uniform(string nom, glm::mat3 matrice);
            void sendVec4Uniform(string nom, glm::vec4 vecteur);
            void sendVec3Uniform(string nom, glm::vec3 vecteur);
            void sendVec2Uniform(string nom, glm::vec2 vecteur);
            void sendIntUniform(string nom, GLuint id);
            void sendFloatUniform(string nom, float val);

            string getVertexShaderFile();
            void setVertexShaderFile(string val);

            string getTessControlShaderFile();
            void setTessControlShaderFile(string val);

            string getTessEvaluationShaderFile();
            void setTessEvaluationShaderFile(string val);

            string getGeometryShaderFile();
            void setGeometryShaderFile(string val);

            string getFragmentShaderFile();
            void setFragmentShaderFile(string val);

        private:
            GLuint m__programID;

            GLuint m__vertexID;
            GLuint m__tessControlID;
            GLuint m__tessEvaluationID;
            GLuint m__geometryID;
            GLuint m__fragmentID;

            string m__vertexShaderFile;
            string m__tessControlShaderFile;
            string m__tessEvaluationShaderFile;
            string m__geometryShaderFile;
            string m__fragmentShaderFile;

            bool compilerShader(GLuint &shader, GLenum type, string const &fichierSource);
    };
}
