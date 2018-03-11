#include "Shader.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace glm;
using namespace LORE;

Shader::Shader(std::string shaderName): m__programID(),
										m__vertexID(),
										m__tessControlID(),
										m__tessEvaluationID(),
										m__geometryID(),
										m__fragmentID(),
										m__vertexShaderFile("Shaders/" + shaderName + "/vertex.shader"),
										m__tessControlShaderFile("Shaders/" + shaderName + "/tessControl.shader"),
										m__tessEvaluationShaderFile("Shaders/" + shaderName + "/tessEvaluation.shader"),
										m__geometryShaderFile("Shaders/" + shaderName + "/geometry.shader"),
										m__fragmentShaderFile("Shaders/" + shaderName + "/fragment.shader")
{
	cout << this << " [Shader] constructor" << endl;
}


Shader::~Shader()
{



}


bool Shader::load()
{
	cout << this << " [Shader] load" << endl;

    // Destruction d'un éventuel ancien Shader
	if (glIsShader(m__vertexID) == GL_TRUE)
		glDeleteShader(m__vertexID);

	/*if (glIsShader(m__tessControlID) == GL_TRUE)
		glDeleteShader(m__tessControlID);

	if (glIsShader(m__tessEvaluationID) == GL_TRUE)
		glDeleteShader(m__tessEvaluationID);

	if (glIsShader(m__geometryID) == GL_TRUE)
		glDeleteShader(m__geometryID);*/

	if (glIsShader(m__fragmentID) == GL_TRUE)
		glDeleteShader(m__fragmentID);

	if (glIsProgram(m__programID) == GL_TRUE)
		glDeleteProgram(m__programID);


    cout << this << " [Shader]: " << m__programID << endl;
	cout << this << " [Shader] load() 1 : " << m__vertexShaderFile << endl;
	cout << this << " [Shader] load() 2 : " << m__fragmentShaderFile << endl;

	// Compilation des shaders
	if (!compilerShader(m__vertexID, GL_VERTEX_SHADER, m__vertexShaderFile))
		return false;

	/*if (!compilerShader(m__tessControlID, GL_TESS_CONTROL_SHADER, m__tessControlShaderFile))
		return false;

	if (!compilerShader(m__tessEvaluationID, GL_TESS_EVALUATION_SHADER, m__tessEvaluationShaderFile))
		return false;

	if (!compilerShader(m__geometryID, GL_GEOMETRY_SHADER, m__geometryShaderFile))
		return false;*/

	if (!compilerShader(m__fragmentID, GL_FRAGMENT_SHADER, m__fragmentShaderFile))
		return false;

	// Création du programme
	m__programID = glCreateProgram();

	// Association des shaders
	glAttachShader(m__programID, m__vertexID);
	//glAttachShader(m__programID, m__tessControlID);
	//glAttachShader(m__programID, m__tessEvaluationID);
	//glAttachShader(m__programID, m__geometryID);
	glAttachShader(m__programID, m__fragmentID);

	// Verrouillage des entrées shader
	glBindAttribLocation(m__programID, 0, "in_Vertex");
	glBindAttribLocation(m__programID, 1, "in_TexCoord0");
	glBindAttribLocation(m__programID, 2, "in_Normal");
	glBindAttribLocation(m__programID, 3, "in_Tangent");
	glBindAttribLocation(m__programID, 4, "in_Bitangent");
	glBindAttribLocation(m__programID, 5, "in_Color");

	// Linkage du programme
	glLinkProgram(m__programID);

	// Vérification du linkage
	GLint erreurLink(0);
	glGetProgramiv(m__programID, GL_LINK_STATUS, &erreurLink);

	// S'il y a eu une erreur
	if (erreurLink != GL_TRUE)
	{
		// Récupération de la taille de l'erreur
		GLint tailleErreur(0);
		glGetProgramiv(m__programID, GL_INFO_LOG_LENGTH, &tailleErreur);

		// Allocation de mémoire
		char *erreur = new char[tailleErreur + 1];

		// Récupération de l'erreur
		glGetShaderInfoLog(m__programID, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';

		// Affichage de l'erreur
		cout << erreur << endl;

		// Libération de la mémoire et retour du booléen false
		delete[] erreur;
		glDeleteProgram(m__programID);

		return false;
	} else { // Sinon c'est que tout s'est bien passé
		return true;
	}
}


bool Shader::compilerShader(GLuint &shader, GLenum type, string const &fichierSource)
{

	// Création du shader
	shader = glCreateShader(type);


	// Vérification du shader
	if (shader == 0)
	{
		std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
		return false;
	}


	// Flux de lecture
	ifstream fichier(fichierSource.c_str());


	// Test d'ouverture
	if (!fichier)
	{
		std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
		glDeleteShader(shader);

		return false;
	}


	// Strings permettant de lire le code source
	std::string ligne;
	std::string codeSource;


	// Lecture
	while (getline(fichier, ligne))
		codeSource += ligne + '\n';


	// Fermeture du fichier
	fichier.close();


	// Récupération de la chaine C du code source
	const GLchar* chaineCodeSource = codeSource.c_str();


	// Envoi du code source au shader
	glShaderSource(shader, 1, &chaineCodeSource, 0);


	// Compilation du shader
	glCompileShader(shader);


	// Vérification de la compilation
	GLint erreurCompilation(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);


	// S'il y a eu une erreur
	if (erreurCompilation != GL_TRUE)
	{

		// Récupération de la taille de l'erreur
		GLint tailleErreur(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);


		// Allocation de mémoire
		char *erreur = new char[tailleErreur + 1];


		// Récupération de l'erreur
		glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';


		// Affichage de l'erreur
		std::cout << erreur << std::endl;


		// Libération de la mémoire et retour du booléen false
		delete[] erreur;
		glDeleteShader(shader);

		return false;
	}


	// Sinon c'est que tout s'est bien passé
	else
		return true;

}


void Shader::sendMat4Uniform(string nom, glm::mat4 matrice)
{

	// Localisation de la matrice
	int localisation = glGetUniformLocation(m__programID, nom.c_str());

	// Envoi des valeurs
	glUniformMatrix4fv(localisation, 1, GL_FALSE, glm::value_ptr(matrice));

}


void Shader::sendMat3Uniform(string nom, glm::mat3 matrice)
{

	// Localisation de la matrice
	int localisation = glGetUniformLocation(m__programID, nom.c_str());

	// Envoi des valeurs
	glUniformMatrix3fv(localisation, 1, GL_FALSE, glm::value_ptr(matrice));

}


void Shader::sendVec4Uniform(std::string nom, glm::vec4 vecteur)
{

	// Localisation de la matrice
	int localisation = glGetUniformLocation(m__programID, nom.c_str());

	// Envoi des valeurs
	glUniform4f(localisation, vecteur.x, vecteur.y, vecteur.z, vecteur.w);

}


void Shader::sendVec3Uniform(std::string nom, glm::vec3 vecteur)
{

	// Localisation de la matrice
	int localisation = glGetUniformLocation(m__programID, nom.c_str());

	// Envoi des valeurs
	glUniform3f(localisation, vecteur.x, vecteur.y, vecteur.z);

}


void Shader::sendVec2Uniform(std::string nom, glm::vec2 vecteur)
{

	// Localisation de la matrice
	int localisation = glGetUniformLocation(m__programID, nom.c_str());

	// Envoi des valeurs
	glUniform2f(localisation, vecteur.x, vecteur.y);

}


void Shader::sendIntUniform(std::string nom, GLuint id)
{

	// Localisation de la matrice
	int localisation = glGetUniformLocation(m__programID, nom.c_str());

	// Envoi des valeurs
	glUniform1i(localisation, id);

}


void Shader::sendFloatUniform(std::string nom, float val)
{

	// Localisation de la matrice
	int localisation = glGetUniformLocation(m__programID, nom.c_str());

	// Envoi des valeurs
	glUniform1f(localisation, val);

}


GLuint Shader::getProgramID()
{
	return m__programID;
}


//=====Shaders=====
string Shader::getVertexShaderFile()
{
	return m__vertexShaderFile;
}


void Shader::setVertexShaderFile(string val)
{
	m__vertexShaderFile = val;
}


string Shader::getTessControlShaderFile()
{
	return m__tessControlShaderFile;
}


void Shader::setTessControlShaderFile(string val)
{
	m__tessControlShaderFile = val;
}


string Shader::getTessEvaluationShaderFile()
{
	return m__tessEvaluationShaderFile;
}


void Shader::setTessEvaluationShaderFile(string val)
{
	m__tessEvaluationShaderFile = val;
}



string Shader::getGeometryShaderFile()
{
	return m__geometryShaderFile;
}


void Shader::setGeometryShaderFile(string val)
{
	m__geometryShaderFile = val;
}



string Shader::getFragmentShaderFile()
{
	return m__fragmentShaderFile;
}


void Shader::setFragmentShaderFile(string val)
{
	m__fragmentShaderFile = val;
}

