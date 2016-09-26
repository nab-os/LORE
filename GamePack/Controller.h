#pragma once

#include <string>
#include <map>
#include <algorithm>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "OpenGL_Window.h"

class Controller
{

	public:

		Controller();
		virtual ~Controller();

		void bind(const int key, std::function<void(void)> action);
		void unbind(const int key);
		void unbind();

		void check(OpenGL_Window* w);

	private:

		std::map<const int, std::function<void(void)>> m__keyBindings;

};

