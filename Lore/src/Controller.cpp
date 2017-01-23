#include "Controller.h"

using namespace std;

Controller::Controller(): m__keyBindings(), m__visibleCursor(false), m__captureCursor(true)
{



}


Controller::~Controller()
{



}


void Controller::bind(const int key, function<void(double dx, double dy)> action)
{

	m__keyBindings.insert(pair<const int, function<void(double dx, double dy)>>(key, action));

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

	double x, y;
	glfwGetCursorPos(w->getWindow(), &x, &y);
	double dx = x - double(w->getWidth())/2, dy = y - double(w->getHeight())/2;

	if(m__mouseEvent)
		m__mouseEvent(x, y, dx, dy);

	for (const auto p : m__keyBindings)
	{

		if (glfwGetKey(w->getWindow(), p.first) == GLFW_PRESS)
		{

			p.second(x, y);

		}

	}

	glfwSetInputMode(w->getWindow(), GLFW_CURSOR, (m__visibleCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN));

	if(m__captureCursor)
		glfwSetCursorPos(w->getWindow(), double(w->getWidth())/2, double(w->getHeight())/2);

}
