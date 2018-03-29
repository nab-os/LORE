#include "Window.h"

#include <iostream>

#include <chrono>
#include <thread>
#include "Thread.h"

using namespace std;
using namespace glm;
using namespace LORE;

LORE::Window::Window(std::string tittle, int width, int height, int fps): m__window(),
																		m__title(tittle),
																		m__width(width),
																		m__height(height),
																		m__frameRate(int(1000/fps)),
																	    m__camera(),
                                                                        m__scene()
{

}


LORE::Window::~Window()
{
	cout << this << " [Window] destructor" << endl;
}


void LORE::Window::error_callback(int error, const char* description)
{
	cout << "[Window] error_callback() :" << description << "\n";
}


void LORE::Window::window_size_callback(GLFWwindow* window, int width, int height)
{
	cout << "[Window] window_size_callback" << endl;
}


void LORE::Window::window_focus_callback(GLFWwindow* window, int state)
{
	cout << "[Window] window_focus_callback: " << state << endl;

	//static_cast<Window*>(glfwGetWindowUserPointer(window))->m__paused = !state;
}

void LORE::Window::window_close_callback(GLFWwindow* window)
{

	cout << "[Window] window_close_callback" << endl;

	Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

	w->close();

}

void LORE::Window::mouse_move_callback(GLFWwindow* window, double x, double y)
{
	//cout << "[Window] mouse_move_callback" << endl;
}


void LORE::Window::load()
{
    cout << this << " [Window] load" << endl;

	// Création de la fenêtre
	m__window = glfwCreateWindow(m__width, m__height, m__title.c_str(), NULL, NULL);
	if (!m__window)
	{

		std::cout << "Erreur lors de la creation de la fenetre" << std::endl;

		glfwTerminate();
		exit(EXIT_FAILURE);

	}

	//glfwSetKeyCallback(m__window, LORE::Window::key_callback);

	glfwMakeContextCurrent(m__window);

	glfwSetInputMode(m__window, GLFW_STICKY_KEYS, 1);

	glfwSetWindowUserPointer(m__window, this);
	glfwSetWindowSizeCallback(m__window, window_size_callback);
	glfwSetWindowFocusCallback(m__window, window_focus_callback);
	glfwSetWindowCloseCallback(m__window, window_close_callback);
	glfwSetCursorPosCallback(m__window, mouse_move_callback);

}


void LORE::Window::close()
{
	glfwSetWindowShouldClose(m__window, GL_TRUE);
}

int LORE::Window::shouldClose()
{
	return glfwWindowShouldClose(m__window);
}


int LORE::Window::startFrame()
{
	int startTime = int(glfwGetTime() * 1000);

	return startTime;
}


void LORE::Window::endFrame(int startTime)
{
	glfwSwapBuffers(m__window);

	glfwPollEvents();

	int endTime = int(glfwGetTime() * 1000);
	int elapsedTime = endTime - startTime;

	//cout << 1.0/elapsedTime*1000 << " fps" << endl;

	if(elapsedTime < m__frameRate)
		Thread::sleep(m__frameRate - elapsedTime);
}


void LORE::Window::render()
{
	glfwMakeContextCurrent(m__window);

	if(m__camera)
		m__camera->render();
}
