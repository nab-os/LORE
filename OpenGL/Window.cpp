#include "stdafx.h"
#include "Window.h"

#include <iostream>

#include <chrono>
#include <thread>

#include "ObjectManager.h"

using namespace std;

Window::Window(std::string tittle, int width, int height, double fps):  m__window(),
																		m__title(tittle),
																		m__width(width),
																		m__height(height),
																		m__frameRate(int(1000/fps)),
																		m__scenes()
{



}


Window::~Window()
{

	for (auto const &pair : m__scenes) {
		
		delete(pair.second);
		
	}

}


void Window::error_callback(int error, const char* description)
{
	std::cout << description << "\n";
}


void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		//glfwSetWindowShouldClose(window, GL_TRUE);

}


void Window::window_size_callback(GLFWwindow* window, int width, int height)
{

	/*
	Window* scene = static_cast<Window*>(glfwGetWindowUserPointer(window));

	scene->m__width = width;
	scene->m__height = height;

	free(scene->m__postProcess);
	scene->m__postProcess = new PostProcessObject(scene->m__width, scene->m__height);
	scene->m__postProcess->charger();*/

}


void Window::window_focus_callback(GLFWwindow* window, int state)
{

	//static_cast<Window*>(glfwGetWindowUserPointer(window))->m__paused = !state;

}


int Window::init()
{

	//glfwSetErrorCallback(SceneOpenGL::error_callback);

	// Initialize our session with the Oculus HMD.
	//if (ovr_Initialize(nullptr) == ovrSuccess)
	//{
		//ovrSession session = nullptr;
		//ovrGraphicsLuid luid;
		/*ovrResult result = ovr_Create(&session, &luid);

		if (result == ovrSuccess)
		{   // Then we're connected to an HMD!

			// Let's take a look at some orientation data.
			ovrTrackingState ts;

			while (true)
			{
				ts = ovr_GetTrackingState(session, 0, true);

				ovrPoseStatef tempHeadPose = ts.HeadPose;
				ovrPosef tempPose = tempHeadPose.ThePose;
				ovrQuatf tempOrient = tempPose.Orientation;

				cout << "Orientation (x,y,z):  " << COLW << tempOrient.x << ","
					<< COLW << tempOrient.y << "," << COLW << tempOrient.z
					<< endl;

				// Wait a bit to let us actually read stuff.
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}

			ovr_Destroy(session);
		}

		ovr_Shutdown();
		// If we've fallen through to this point, the HMD is no longer
		// connected.*/
	//}



	/*
	vr::EVRInitError eError = vr::VRInitError_None;
	vr::IVRSystem *m_pHMD = vr::VR_Init(&eError, vr::VRApplication_Scene);

	if (eError != vr::VRInitError_None)
	{
		m_pHMD = NULL;
		char buf[1024];
		//sprintf_s(buf, sizeof(buf), "Unable to init VR runtime: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
		return false;
	}


	vr::IVRRenderModels* m_pRenderModels = nullptr;//(vr::IVRRenderModels *)vr::VR_GetGenericInterface(vr::IVRRenderModels_Version, &eError);
	if (!m_pRenderModels)
	{
		m_pHMD = NULL;
		//vr::VR_Shutdown();

		char buf[1024];
		//sprintf_s(buf, sizeof(buf), "Unable to get render model interface: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
		return false;
	}
	*/
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


	glfwSetKeyCallback(m__window, Window::key_callback);

	glfwMakeContextCurrent(m__window);

	glfwSetInputMode(m__window, GLFW_STICKY_KEYS, 1);

	glfwSetWindowUserPointer(m__window, this);
	glfwSetWindowSizeCallback(m__window, window_size_callback);
	glfwSetWindowFocusCallback(m__window, window_focus_callback);
	

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


int Window::shouldClose()
{
	return glfwWindowShouldClose(m__window);
}


int Window::startFrame()
{
	
	int startTime = int(glfwGetTime() * 1000);



	return startTime;

}


void Window::endFrame(int startTime)
{
	
	glfwSwapBuffers(m__window);

	//glfwPollEvents();

	int endTime = int(glfwGetTime() * 1000);
	int elapsedTime = endTime - startTime;

	//cout << elapsedTime << endl;
	
	if(elapsedTime < m__frameRate)
		this_thread::sleep_for(std::chrono::milliseconds(m__frameRate - elapsedTime));

}


void Window::render() 
{

	for (std::pair<std::string, Scene*> p : m__scenes) 
	{
	
		p.second->render();
	
	}

}


Scene* Window::addScene(string name)
{
	
	Scene* scene = (Scene*)ObjectManager::get("scene");
	this->addScene(name, scene);
	return scene;

}


void Window::addScene(string name, Scene* scene)
{

	m__scenes.insert(pair<string, Scene*>(name, scene));

}


Scene* Window::getScene(string name)
{

	return m__scenes.find(name)->second;

}