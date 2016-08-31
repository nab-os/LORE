#pragma once

#include <string>

#include "Object.h"

class ObjectManager
{

	public:

		virtual ~ObjectManager();

		static Object* get(std::string path);

	private:
		
		ObjectManager();

};

