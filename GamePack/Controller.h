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

		void bind(const int key, std::function<void(double x, double y)> action);
		void unbind(const int key);
		void unbind();

		void check(OpenGL_Window* w);

		void setMouseEvent(std::function<void(double x, double y, double dx, double dy)> event) { m__mouseEvent = event; };

		void toggleVisibleCursor() { m__visibleCursor = !m__visibleCursor; };
		void toggleCaptureCursor() { m__captureCursor = !m__captureCursor; };

	private:

		std::map<const int, std::function<void(double x, double y)>> m__keyBindings;

		std::function<void(double x, double y, double dx, double dy)> m__mouseEvent;

		bool m__visibleCursor;
		bool m__captureCursor;

};

