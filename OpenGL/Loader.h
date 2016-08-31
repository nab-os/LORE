#pragma once

#include <string>

class Loader
{

	public:

		Loader();
		virtual ~Loader();

		void* load(std::string path = "/Objects/default") {};

	private:



};

