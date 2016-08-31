#pragma once

#include <string>
#include <map>

#include "Object.h"

class ObjectLibrary
{

	public:

		virtual ~ObjectLibrary();

		static ObjectLibrary* getInstance();

		bool has(std::string path);
		void add(std::string path, Object* object);
		Object* get(std::string path);

		void flush();

	private:
		
		std::map<std::string, Object*> m__objects;

		static ObjectLibrary* m__instance;

		ObjectLibrary();

};

