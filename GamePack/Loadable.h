#pragma once

#include <iostream>
#include <string>

class Loadable
{

	public:

		Loadable();
		virtual ~Loadable();

		void load();
		void unload();

		bool loaded() { return m__loaded; };

	protected:

		bool m__loaded;

};

