#include "Controller.h"

using namespace std;

Controller::Controller(): m__keyBindings()
{



}


Controller::~Controller()
{



}


void Controller::bind(const int key, function<void(void)> action)
{

	m__keyBindings.insert(pair<const int, function<void(void)>>(key, action));

}


void Controller::unbind(const int key)
{

	m__keyBindings.erase(key);

}


void Controller::unbind()
{

	m__keyBindings.clear();

}


void Controller::check(OpenGL_Window* w)
{

	for (const auto p : m__keyBindings)
	{

		if (glfwGetKey(w->getWindow(), p.first) == GLFW_PRESS)
		{

			p.second();

		}

	}

}
