#include "MaterialLoader.h"

#include <regex>

using namespace std;

MaterialLoader::MaterialLoader(std::string name) : Loader("Objects/" + name + "/" + name + ".mtl", name), m__materials()
{



}


MaterialLoader::~MaterialLoader()
{



}


std::map<std::string, Material*> MaterialLoader::load()
{

	cout << this << " [MaterialLoader] : load" << endl;

	if (ouvrir()) {

		m__materials.clear();

		string code;
		std::regex reg_material("^newmtl");

		setPositionCurseur(0, DEBUT);
		while (!m__fichier->eof())
		{

			*m__fichier >> code;

			//cout << "[MaterialLoader] load() : code : " << code << endl;
			if (std::regex_match(code, reg_material))
			{

				chargerMaterial();

			}

			m__fichier->ignore(200, '\n');

		}

		fermer();

	}

	return m__materials;

}


void MaterialLoader::chargerMaterial()
{

	string code;

	std::string nom;
	*m__fichier >> nom;
	//cout << "[MaterialLoader] chargerMaterial() : new material : " << nom << endl;

	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	std::string diffuseTexture = "default.png";
	std::string specularTexture = "default.png";

	//==Regex de detection de lignes==//
	std::regex reg_diffuse_color("^Kd");
	std::regex reg_specular_color("^Ks");
	std::regex reg_diffuse_texture("^map_Kd");
	std::regex reg_specular_texture("^map_Ks");
	std::regex reg_material("^newmtl");

	while (!m__fichier->eof())
	{

		*m__fichier >> code;
		//cout << "[MaterialLoader] chargerMaterial() : code : " << code << endl;

		if (std::regex_match(code, reg_material)) //Si c'est un autre objet
		{

			chargerMaterial();

		}
		else if (std::regex_match(code, reg_diffuse_color)) //Si c'est la couleur diffuse
		{
			diffuseColor = getVec3();
		}
		else if (std::regex_match(code, reg_specular_color)) //Si c'est la couleur spéculaire
		{
			specularColor = getVec3();
		}
		else if (std::regex_match(code, reg_diffuse_texture)) //Si c'est la couleur spéculaire
		{
			diffuseTexture = getString();
		}
		else if (std::regex_match(code, reg_specular_texture)) //Si c'est la couleur spéculaire
		{
			specularTexture = getString();
		}

		m__fichier->ignore(200, '\n');

	}

	Material* mat = new Material();

	Shader* shader = new Shader();

	Texture* textureD = new Texture(diffuseTexture);
	Texture* textureS = new Texture(specularTexture);

	mat->setShader(shader);
	mat->setDiffuseColor(diffuseColor);
	mat->setSpecularColor(specularColor);
	mat->setDiffuseTexture(textureD);
	mat->setSpecularTexture(textureS);

	m__materials.insert(std::pair<std::string, Material*>(nom, mat));

}
