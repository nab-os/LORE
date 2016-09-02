#include "stdafx.h"
#include "ObjectLoader.h"

using namespace std;

ObjectLoader::ObjectLoader(std::string path): Loader(path)
{



}


ObjectLoader::~ObjectLoader()
{



}


Object* ObjectLoader::load()
{
	
	cout << "[ObjectLoader] : load" << endl;

	Object* root = new Object();

	int tailleFichier;

	if(ouvrir()){

		cout << "[ObjectLoader] : load() : fichier ouvert avec succes" << endl;
		char caractere = '0';
		setPositionCurseur(0, DEBUT);

		while (!m__fichier->eof())
		{

			cout << "[ObjectLoader] : load() : test : " << caractere << endl;

			m__fichier->getline(caractere, 1);

			if (caractere == 'o')
			{
				chargerObjet(root);

			}

		}

		fermer();

	}

	return root;

}


void ObjectLoader::chargerObjet(Object* parent)
{
	char caractere = '0';
	bool continuer = true;

	std::string material_name;
	std::string nom;
	
	std::vector<glm::vec3> indicesVertices;
	std::vector<glm::vec3> indicesNormals;
	std::vector<glm::vec3> indicesCoordTextures;

	std::vector<glm::vec3> finalVertices;
	std::vector<glm::vec2> finalCoordTextures;
	std::vector<glm::vec3> finalNormals;

	setPositionCurseur(1, CURSEUR);

	while (caractere != '\n')
	{
		m__fichier->get(caractere);
		if (caractere != '\n')
			nom.push_back(caractere);
	}
	setPositionCurseur(-2, CURSEUR);

	while (continuer)
	{
		m__fichier->get(caractere);
		if (caractere == '\n')
		{
			m__fichier->get(caractere);
			if ((caractere == 'o') || (m__fichier->eof()))
			{
				setPositionCurseur(-2, CURSEUR);

				continuer = false;

			}

			if (caractere == 'v')
			{

				m__fichier->get(caractere);
				if (caractere == ' ') //Si c'est un vertice
				{
					std::vector<glm::vec3> temp = chargerVertice();
					finalVertices.insert(finalVertices.end(), temp.begin(), temp.end());
				}

				if (caractere == 't') //Si c'est une coordonné de texture
				{
					std::vector<glm::vec2> temp = chargerCoordTexture();
					finalCoordTextures.insert(finalCoordTextures.end(), temp.begin(), temp.end());
				}

				if (caractere == 'n') //Si c'est une normale
				{
					std::vector<glm::vec3> temp = chargerNormale();
					finalNormals.insert(finalNormals.end(), temp.begin(), temp.end());
				}

			}

			if (caractere == 'u')
			{
				material_name = chargerMaterial();
			}

			if (caractere == 'f') //Si c'est une face
			{
				chargerFace(&indicesVertices, &indicesCoordTextures, &indicesNormals);
			}
		}
	}

	ModelRender* model = new ModelRender();
	model->setVertices(finalVertices);
	
	parent->setRenderModel(model);
	
	/*
	FichierMTL fichierM(m_emplacementFichier, material_name);
	fichierM.ouvrir();
	fichierM.charger();


	m_objets.push_back(new ObjectData(nom));





	float* tempVert = (float*)malloc(sizeof(float) * m_vertices.size());
	for (unsigned int i = 0; i < m_vertices.size(); i++) { tempVert[i] = m_vertices[i]; }

	m_objets[m_objets.size() - 1]->setVertices(tempVert);
	m_objets[m_objets.size() - 1]->setVerticesCount(m_vertices.size() / 3);


	float* tempVertIndices = (float*)malloc(sizeof(float) * indicesVertices.size());
	for (unsigned int i = 0; i < indicesVertices.size(); i++) { tempVertIndices[i] = indicesVertices[i]; }

	m_objets[m_objets.size() - 1]->setVerticesIndices(tempVertIndices);
	m_objets[m_objets.size() - 1]->setVerticesIndicesCount(indicesVertices.size() / 3);






	float* tempNormal = (float*)malloc(sizeof(float) * m_normales.size());
	for (unsigned int i = 0; i < m_normales.size(); i++) { tempNormal[i] = m_normales[i]; }

	m_objets[m_objets.size() - 1]->setNormals(tempNormal);
	m_objets[m_objets.size() - 1]->setNormalsCount(m_normales.size() / 3);



	float* tempNormalIndices = (float*)malloc(sizeof(float) * indicesNormals.size());
	for (unsigned int i = 0; i < indicesNormals.size(); i++) { tempNormalIndices[i] = indicesNormals[i]; }

	m_objets[m_objets.size() - 1]->setNormals(tempNormalIndices);
	m_objets[m_objets.size() - 1]->setNormalsCount(indicesNormals.size() / 3);






	float* tempCoords = (float*)malloc(sizeof(float) * m_coordTexture.size());
	for (unsigned int i = 0; i < m_coordTexture.size(); i++) { tempCoords[i] = m_coordTexture[i]; }

	m_objets[m_objets.size() - 1]->setCoords(tempCoords);
	m_objets[m_objets.size() - 1]->setCoordsCount(m_coordTexture.size() / 2);



	float* tempCoordsIndices = (float*)malloc(sizeof(float) * indicesCoordTextures.size());
	for (unsigned int i = 0; i < indicesCoordTextures.size(); i++) { tempCoordsIndices[i] = indicesCoordTextures[i]; }

	m_objets[m_objets.size() - 1]->setCoords(tempCoordsIndices);
	m_objets[m_objets.size() - 1]->setCoordsCount(indicesCoordTextures.size() / 2);




	Material* mat = new Material(material);

	std::string nomTextureDiffuse = fichierM.getEmplacementTextureDiffuse();
	if (nomTextureDiffuse.size() > 0)
	{

		mat->setUtilisationDiffuse(true);

		std::string ext = ".png";
		unsigned int pos = nomTextureDiffuse.find(ext);
		if (pos != std::string::npos)
			nomTextureDiffuse.erase(pos, ext.length());

		mat->setTextureDiffuse(TextureLibrary::getInstance()->get(nomTextureDiffuse));

	}
	else
	{

		mat->setUtilisationDiffuse(false);

	}

	std::string nomTextureNormal = fichierM.getEmplacementTextureNormal();
	if (nomTextureNormal.size() > 0)
	{

		mat->setUtilisationNormal(true);

		std::string ext = ".png";
		unsigned int pos = nomTextureNormal.find(ext);
		if (pos != std::string::npos)
			nomTextureNormal.erase(pos, ext.length());

		mat->setTextureNormal(TextureLibrary::getInstance()->get(nomTextureNormal));

	}
	else
	{

		mat->setUtilisationNormal(false);

	}


	std::string nomTextureSpecular = fichierM.getEmplacementTextureSpecular();
	if (nomTextureSpecular.size() > 0)
	{

		mat->setUtilisationSpecular(true);

		std::string ext = ".png";
		unsigned int pos = nomTextureSpecular.find(ext);
		if (pos != std::string::npos)
			nomTextureSpecular.erase(pos, ext.length());

		mat->setTextureSpecular(TextureLibrary::getInstance()->get(nomTextureSpecular));

	}
	else
	{

		mat->setUtilisationSpecular(false);

	}


	std::string nomTextureDisplacement = fichierM.getEmplacementTextureDisplacement();
	if (nomTextureDisplacement.size() > 0)
	{

		mat->setUtilisationDisplacement(true);

		std::string ext = ".png";
		unsigned int pos = nomTextureDisplacement.find(ext);
		if (pos != std::string::npos)
			nomTextureDisplacement.erase(pos, ext.length());

		mat->setTextureDisplacement(TextureLibrary::getInstance()->get(nomTextureDisplacement));

	}
	else
	{

		mat->setUtilisationDisplacement(false);

	}

	mat->setShader(ShaderLibrary::getInstance()->get("all"));
	mat->setShaderOmbre(ShaderLibrary::getInstance()->get("light"));
	mat->setColorDiffuse(Color(fichierM.getCouleur().x, fichierM.getCouleur().y, fichierM.getCouleur().z, fichierM.getCouleur().w));


	m_objets[m_objets.size() - 1]->setMaterial(MaterialLibrary::getInstance()->add(material, mat));

	fichierM.fermer();

	setPositionCurseur(-2, CURSEUR);*/

}


std::vector<glm::vec3> ObjectLoader::chargerVertice()
{

	std::vector<glm::vec3> vertices;

	setPositionCurseur(-1, CURSEUR);

	float x, y, z;

	*m__fichier >> x >> y >> z;

	vertices.push_back(glm::vec3(x, y, z));

	return vertices;
}


std::vector<glm::vec2> ObjectLoader::chargerCoordTexture()
{
	float value = 0;
	std::vector<glm::vec2> coordTexture;

	setPositionCurseur(1, CURSEUR);

	float x, y;

	*m__fichier >> x >> y;

	coordTexture.push_back(glm::vec2(x, y));

	return coordTexture;
}


std::vector<glm::vec3> ObjectLoader::chargerNormale()
{

	std::vector<glm::vec3> normales;

	setPositionCurseur(-1, CURSEUR);

	float x, y, z;

	*m__fichier >> x >> y >> z;

	normales.push_back(glm::vec3(x, y, z));

	return normales;
}


void ObjectLoader::chargerFace(std::vector<glm::vec3> *facesVertices, std::vector<glm::vec3> *facesCoordTexture, std::vector<glm::vec3> *facesNormals)
{

	unsigned int vertex_1, vertex_2, vertex_3;
	unsigned int coordTexture_1, coordTexture_2, coordTexture_3;
	unsigned int normal_1, normal_2, normal_3;

	*m__fichier >> vertex_1 >> coordTexture_1 >> normal_1;
	*m__fichier >> vertex_2 >> coordTexture_2 >> normal_2;
	*m__fichier >> vertex_3 >> coordTexture_3 >> normal_3;

	facesVertices->push_back(glm::vec3(vertex_1, vertex_2, vertex_3));
	facesCoordTexture->push_back(glm::vec3(coordTexture_1, coordTexture_2, coordTexture_3));
	facesNormals->push_back(glm::vec3(normal_1, normal_2, normal_3));
		
}


std::vector<glm::vec3> ObjectLoader::associerVertexIndices(std::vector<glm::vec3> vertices, std::vector<glm::vec3> indices)
{

	std::vector<glm::vec3> finalVertices;

	for (unsigned int i = 0; i < indices.size(); i++)
	{
		
		for (unsigned int j = 0; j < 3; j++)
		{

			finalVertices.push_back(vertices[indices[i][j]]);

		}

	}
	return indices;
}


std::vector<glm::vec2> ObjectLoader::associerCoordTextureFaces(std::vector<glm::vec2> coordTextures, std::vector<glm::vec3> indices)
{

	std::vector<glm::vec2> finalCoordTextures;

	for (unsigned int i = 0; i < indices.size(); i++)
	{

		for (unsigned int j = 0; j < 3; j++)
		{

			finalCoordTextures.push_back(coordTextures[indices[i][j]]);

		}

	}
	return finalCoordTextures;
}


std::vector<glm::vec3> ObjectLoader::associerNormalIndices(std::vector<glm::vec3> normals, std::vector<glm::vec3> indices)
{

	std::vector<glm::vec3> finalNormals;

	for (unsigned int i = 0; i < indices.size(); i++)
	{

		for (unsigned int j = 0; j < 3; j++)
		{

			finalNormals.push_back(normals[indices[i][j]]);

		}

	}
	return finalNormals;
}


std::string ObjectLoader::chargerMaterial()
{
	std::string material;
	char caractere = '0';
	while (caractere != ' ')
	{
		m__fichier->get(caractere);
	}
	while (caractere != '\n')
	{
		m__fichier->get(caractere);
		material.push_back(caractere);
	}
	material.erase(material.size() - 1);

	setPositionCurseur(-1, CURSEUR);
	return material;

}
