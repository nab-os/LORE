#pragma once

#include <string>
#include <map>

#include "Model.h"

class ModelLibrary
{

	public:

		virtual ~ModelLibrary();

		static ModelLibrary* getInstance();

		bool has(std::string path);
		void add(std::string path, Model* model);
		Model* get(std::string path);

		void flush();

	private:
		
		std::map<std::string, Model*> m__models;

		static ModelLibrary* m__instance;

		ModelLibrary();

};

