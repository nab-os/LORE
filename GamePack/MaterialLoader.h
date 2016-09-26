#pragma once


#include <map>

#include "Loader.h"
#include "Material.h"

class MaterialLoader : public Loader
{

	public:

		MaterialLoader(std::string name = "default");
		virtual ~MaterialLoader();

		std::map<std::string, Material*> load();

	private:

		void chargerMaterial();

		glm::vec3 chargerDiffuseColor();
		glm::vec3 chargerSpecularColor();

		std::map<std::string, Material*> m__materials;
		
};

