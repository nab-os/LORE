#pragma once

#include <string>
#include <map>

#include "Material.h"

class MaterialLibrary
{

	public:

		MaterialLibrary();
		~MaterialLibrary();

		static MaterialLibrary* getInstance();

		bool has(std::string path);
		void add(std::string path, Material* object);
		Material* get(std::string path);

		void flush();

private:

	std::map<std::string, Material*> m__materials;

	static MaterialLibrary* m__instance;

};

