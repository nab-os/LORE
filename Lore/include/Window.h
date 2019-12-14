#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Scene.h"

namespace LORE {
    class Window {
        public:
            Window(std::string tittle = "First window", int width = 512, int height = 512, int fps = 60);
            virtual ~Window();

            void close();

            int shouldClose();

            int startFrame();
            void endFrame(int startTime);

            void step();
            void render();
            void load();

            GLFWwindow* getWindow() { return m__window; };
            void setCamera(Camera* camera) { m__camera = camera; };
            Camera* getCamera() { return m__camera; };

            void setScene(Scene* scene) { m__scene = scene; };
            Scene* getScene() { return m__scene; };

            int getWidth() { return m__width; };
            int getHeight() { return m__height; };

        private:
            GLFWwindow* m__window;

            std::string m__title;

            int m__width;
            int m__height;

            int m__frameRate;

            Camera* m__camera;
            Scene* m__scene;

            static void error_callback(int error, const char* description);

            static void window_size_callback(GLFWwindow* window, int width, int height);
            static void window_focus_callback(GLFWwindow* window, int state);
            static void window_close_callback(GLFWwindow* window);
            static void mouse_move_callback(GLFWwindow* window, double x, double y);
    };
}
