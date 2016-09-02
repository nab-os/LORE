#pragma once

#include "Loader.h"
#include "Object.h"
#include "ModelRender.h"

#include <deque>
#include <string>

#include "TextureLibrary.h"
#include "MaterialLibrary.h"

class ObjectLoader: public Loader
{

	public:

		ObjectLoader(std::string path = "/Objects/default");
		virtual ~ObjectLoader();

		Object* load();


	private:

		void chargerObjet(Object* parent);
		std::vector<glm::vec3> chargerVertice();
		std::vector<glm::vec2> chargerCoordTexture();
		std::vector<glm::vec3> chargerNormale();
		void chargerFace(std::vector<glm::vec3> *facesVertices, std::vector<glm::vec3> *facesCoordTexture, std::vector<glm::vec3> *facesNormals);
		std::vector<glm::vec2> associerCoordTextureFaces(std::vector<glm::vec2> coordTextures, std::vector<glm::vec3> facesCoordTexture);
		std::vector<glm::vec3> associerVertexIndices(std::vector<glm::vec3> vertices, std::vector<glm::vec3> indices);
		std::vector<glm::vec3> associerNormalIndices(std::vector<glm::vec3> normals, std::vector<glm::vec3> indices);
		std::string chargerMaterial();
				
};

