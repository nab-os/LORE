#pragma once

#include <vector>
#include <map>
#include <string>

#include "Loader.h"
#include "Object.h"
#include "ModelRender.h"

#include "TextureLibrary.h"
#include "Material.h"
#include "MaterialLoader.h"

class ObjectLoader: public Loader
{

	public:

		ObjectLoader(std::string name = "default");
		virtual ~ObjectLoader();

		Object* load();


	private:

		void chargerObjet(Object* parent);
		std::vector<glm::vec3> chargerVertice();
		std::vector<glm::vec2> chargerCoordTexture();
		std::vector<glm::vec3> chargerNormale();
		void chargerFace(std::vector<glm::ivec3> *facesVertices, std::vector<glm::ivec3> *facesCoordTexture, std::vector<glm::ivec3> *facesNormals);
		std::vector<glm::vec3> associerVertexIndices(std::vector<glm::vec3> vertices, std::vector<glm::ivec3> indices);
		std::vector<glm::vec2> associerCoordTextureFaces(std::vector<glm::vec2> coordTextures, std::vector<glm::ivec3> indices);
		std::vector<glm::vec3> associerNormalIndices(std::vector<glm::vec3> normals, std::vector<glm::ivec3> indices);
		Material* chargerMaterial();

		std::vector<glm::vec3> m__vertices;
		std::vector<glm::vec2> m__coordTextures;
		std::vector<glm::vec3> m__normals;

		std::map<std::string, Material*> m__materials;
		
};

