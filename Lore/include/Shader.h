#pragma once

#include <string>

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LORE {
    class Shader {
        public:
            Shader(std::string shaderName = "default");
            virtual ~Shader();

            bool load();

            GLuint getProgramID();

            void sendMat4Uniform(std::string nom, glm::mat4 matrice);
            void sendMat3Uniform(std::string nom, glm::mat3 matrice);
            void sendVec4Uniform(std::string nom, glm::vec4 vecteur);
            void sendVec3Uniform(std::string nom, glm::vec3 vecteur);
            void sendVec2Uniform(std::string nom, glm::vec2 vecteur);
            void sendIntUniform(std::string nom, GLuint id);
            void sendFloatUniform(std::string nom, float val);

            std::string getVertexShaderFile();
            void setVertexShaderFile(std::string val);

            std::string getTessControlShaderFile();
            void setTessControlShaderFile(std::string val);

            std::string getTessEvaluationShaderFile();
            void setTessEvaluationShaderFile(std::string val);

            std::string getGeometryShaderFile();
            void setGeometryShaderFile(std::string val);

            std::string getFragmentShaderFile();
            void setFragmentShaderFile(std::string val);

        private:
            GLuint m__programID;

            GLuint m__vertexID;
            GLuint m__tessControlID;
            GLuint m__tessEvaluationID;
            GLuint m__geometryID;
            GLuint m__fragmentID;

            std::string m__vertexShaderFile;
            std::string m__tessControlShaderFile;
            std::string m__tessEvaluationShaderFile;
            std::string m__geometryShaderFile;
            std::string m__fragmentShaderFile;

            bool compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource);
    };
}
