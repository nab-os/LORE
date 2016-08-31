#pragma once

#include <string>
#include <map>
#include <algorithm>
#include <functional>

class Controller
{

	public:

		Controller();
		virtual ~Controller();

		void bind(const int key, std::function<void(void)> action);
		void unbind(const int key);
		void unbind();

	private:

		std::map<const int, std::function<void(void)>> m__keyBindings;

};

