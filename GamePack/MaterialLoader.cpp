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

	cout << "[MaterialLoader] : load" << endl;

	if (ouvrir()) {

		m__materials.clear();

		string code;
		std::regex reg_material("^newmtl");

		setPositionCurseur(0, DEBUT);
		while (!m__fichier->eof())
		{

			*m__fichier >> code;

			cout << "[MaterialLoader] load() : code : " << code << endl;
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
	cout << "[MaterialLoader] chargerMaterial() : new material : " << nom << endl;

	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	//==Regex de detection de lignes==//
	std::regex reg_diffuse_color("^Kd");
	std::regex reg_specular_color("^Ks");
	std::regex reg_material("^newmtl");

	while (!m__fichier->eof())
	{

		*m__fichier >> code;
		cout << "[MaterialLoader] chargerMaterial() : code : " << code << endl;

		if (std::regex_match(code, reg_material)) //Si c'est un autre objet
		{

			chargerMaterial();

		}
		else if (std::regex_match(code, reg_diffuse_color)) //Si c'est la couleur diffuse
		{
			diffuseColor = chargerDiffuseColor();
		}
		else if (std::regex_match(code, reg_specular_color)) //Si c'est la couleur spéculaire
		{
			specularColor = chargerSpecularColor();
		}

		m__fichier->ignore(200, '\n');

	}

	Material* mat = new Material();

	Shader* shader = new Shader();

	mat->setShader(shader);
	mat->setDiffuseColor(diffuseColor);
	mat->setSpecularColor(specularColor);

	m__materials.insert(std::pair<std::string, Material*>(nom, mat));

}


glm::vec3 MaterialLoader::chargerDiffuseColor()
{

	float r, g, b;

	*m__fichier >> r >> g >> b;

	cout << "[MaterialLoader] chargerDiffuseColor() : " << r << " " << g << " " << b << endl;

	return glm::vec3(r, g, b);

}


glm::vec3 MaterialLoader::chargerSpecularColor()
{

	float r, g, b;

	*m__fichier >> r >> g >> b;

	return glm::vec3(r, g, b);

}
