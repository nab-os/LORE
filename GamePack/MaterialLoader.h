#pragma once


#include <string>
#include <map>

#include "Loader.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"

class MaterialLoader : public Loader
{

	public:

		MaterialLoader(std::string name = "default");
		virtual ~MaterialLoader();

		std::map<std::string, Material*> load();

	private:

		void chargerMaterial();

		std::map<std::string, Material*> m__materials;
		
};

