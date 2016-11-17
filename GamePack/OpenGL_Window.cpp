//#include "stdafx.h"
#include "OpenGL_Window.h"

#include <iostream>

#include <chrono>
#include <thread>

#include "ObjectManager.h"

using namespace std;
using namespace glm;

OpenGL_Window::OpenGL_Window(std::string tittle, int width, int height, int fps): m__window(),
																		m__title(tittle),
																		m__width(width),
																		m__height(height),
																		m__frameRate(int(1000/fps))
{

	m__scene = new Scene();
	m__camera = new Camera(width, height, vec3(0, 0, 0), vec3(0, 0, 1), vec3(0.0, 1.0, 0.0));

    m__camera->setScene(m__scene);

    m__camera->disablePhysics();
    m__camera->setBackgroundColor(vec3(0.2, 0.0, 0.2));
    m__camera->setProjection(ortho(0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f));
    //m__camera->setProjection(ortho((float)width / -2, (float)width / 2, 0.0f, (float)height, 0.001f, 10000.0f));

}


OpenGL_Window::~OpenGL_Window()
{

	cout << this << " [Window] destructor" << endl;
	if(m__scene)
		delete m__scene;
	if(m__camera)
		delete m__camera;

}


void OpenGL_Window::error_callback(int error, const char* description)
{
	cout << "[Window] error_callback() :" << description << "\n";
}


void OpenGL_Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	cout << "[Window] key_callback" << endl;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

}


void OpenGL_Window::window_size_callback(GLFWwindow* window, int width, int height)
{

	cout << "[Window] window_size_callback" << endl;

}


void OpenGL_Window::window_focus_callback(GLFWwindow* window, int state)
{

	cout << "[Window] window_focus_callback" << endl;

	//static_cast<Window*>(glfwGetWindowUserPointer(window))->m__paused = !state;

}

void OpenGL_Window::window_close_callback(GLFWwindow* window)
{

	cout << "[Window] window_close_callback" << endl;

	OpenGL_Window* w = static_cast<OpenGL_Window*>(glfwGetWindowUserPointer(window));

	w->close();

}

void OpenGL_Window::mouse_move_callback(GLFWwindow* window, double x, double y)
{

	//cout << "[Window] mouse_move_callback" << endl;

}


int OpenGL_Window::init()
{

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {

		std::cout << "Failed to initialize GLFW\n";
		return -1;

	}

	// Création de la fenêtre
	m__window = glfwCreateWindow(m__width, m__height, m__title.c_str(), NULL, NULL);
	if (!m__window)
	{

		std::cout << "Erreur lors de la creation de la fenetre" << std::endl;

		glfwTerminate();
		exit(EXIT_FAILURE);

		return false;

	}


	glfwSetKeyCallback(m__window, OpenGL_Window::key_callback);

	glfwMakeContextCurrent(m__window);

	glfwSetInputMode(m__window, GLFW_STICKY_KEYS, 1);

	glfwSetWindowUserPointer(m__window, this);
	glfwSetWindowSizeCallback(m__window, window_size_callback);
	glfwSetWindowFocusCallback(m__window, window_focus_callback);
	glfwSetWindowCloseCallback(m__window, window_close_callback);
	glfwSetCursorPosCallback(m__window, mouse_move_callback);

	//=====================


	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


	// On initialise GLEW
	GLenum initialisationGLEW(glewInit());

	// Si l'initialisation a échoué :
	if (initialisationGLEW != GLEW_OK)
	{

		// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
		std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

		glfwTerminate();
		exit(EXIT_FAILURE);

		return false;
	}

	return true;
}


void OpenGL_Window::close()
{

	glfwSetWindowShouldClose(m__window, GL_TRUE);

}

int OpenGL_Window::shouldClose()
{
	return glfwWindowShouldClose(m__window);
}


int OpenGL_Window::startFrame()
{

	int startTime = int(glfwGetTime() * 1000);



	return startTime;

}


void OpenGL_Window::endFrame(int startTime)
{

	glfwSwapBuffers(m__window);

	glfwPollEvents();

	int endTime = int(glfwGetTime() * 1000);
	int elapsedTime = endTime - startTime;

	//cout << elapsedTime << endl;

	if(elapsedTime < m__frameRate)
		this_thread::sleep_for(std::chrono::milliseconds(m__frameRate - elapsedTime));

}


void OpenGL_Window::render()
{

	glfwMakeContextCurrent(m__window);
	m__camera->render();

}


void OpenGL_Window::load()
{

    cout << this << " [OpenGL_Window] load" << endl;

    m__scene->load();
    m__camera->load();

    //m__scene->addObject(m__camera);

}
