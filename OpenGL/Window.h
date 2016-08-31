#pragma once

#include <string>
#include <map>

#if defined(_WIN32)
 #define GLFW_EXPOSE_NATIVE_WIN32
 #define GLFW_EXPOSE_NATIVE_WGL
 #define OVR_OS_WIN32
#elif defined(__APPLE__)
 #define GLFW_EXPOSE_NATIVE_COCOA
 #define GLFW_EXPOSE_NATIVE_NSGL
 #define OVR_OS_MAC
#elif defined(__linux__)
 #define GLFW_EXPOSE_NATIVE_X11
 #define GLFW_EXPOSE_NATIVE_GLX
 #define OVR_OS_LINUX
#endif

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Scene.h"


#include <OVR_CAPI.h>
#include <OVR_CAPI_GL.h>


class Window
{

	public:

		Window(std::string tittle = "First window", int width = 512, int height = 512, double fps = 60);
		virtual ~Window();

		int init();

		int shouldClose();

		int startFrame();
		void endFrame(int startTime);

		void render();

		Scene* addScene(std::string name);
		void addScene(std::string name, Scene* scene);
		Scene* getScene(std::string name);

	private:

		GLFWwindow* m__window;

		std::string m__title;

		int m__width;
		int m__height;
		
		int m__frameRate;

		std::map<std::string, Scene*> m__scenes;

		static void error_callback(int error, const char* description);

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void window_size_callback(GLFWwindow* window, int width, int height);
		static void window_focus_callback(GLFWwindow* window, int state);

};

