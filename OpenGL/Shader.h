#pragma once

#include <string>

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{

	public:

		Shader(std::string shaderName = "default");
		virtual ~Shader();

		bool charger();

		GLuint getProgramID();


		void envoyerMat4(std::string nom, glm::mat4 matrice);
		void envoyerMat3(std::string nom, glm::mat3 matrice);
		void envoyerVec4(std::string nom, glm::vec4 vecteur);
		void envoyerVec3(std::string nom, glm::vec3 vecteur);
		void envoyer1I(std::string nom, GLuint id);
		void envoyerFloat(std::string nom, float val);


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

