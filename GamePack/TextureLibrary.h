#pragma once

#include <string>
#include <map>

#include "Texture.h"

class TextureLibrary
{

	public:

		TextureLibrary();
		~TextureLibrary();

		static TextureLibrary* getInstance();

		bool has(std::string path);
		void add(std::string path, Texture* object);
		Texture* get(std::string path);

		void flush();

private:

	std::map<std::string, Texture*> m__textures;

	static TextureLibrary* m__instance;

};

