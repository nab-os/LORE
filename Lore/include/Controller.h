#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <mutex>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Window.h"

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::function;
using std::mutex;

namespace LORE {
    enum KeyState {
        PRESSED,
        PRESSING,
        RELEASED
    };

    class Controller {
        private:
            static map<const int, int> m_key_states;
            static map<const int, int> m_last_key_states;

            static map<const int, int> m_click_states;
            static map<const int, int> m_last_click_states;

            static int m_wheel_state;

            static glm::vec2 m_mouse_pos;
            static glm::vec2 m_last_mouse_pos;
            static glm::vec2 m_origin_mouse_pos;

            static mutex m_key_mutex;
            static mutex m_mouse_mutex;
            static mutex m_click_mutex;
            static mutex m_wheel_mutex;

            // [keys, action] key release event
            map<const vector<int>, function<void()>> m_key_pressed_bindings;
            map<const vector<int>, function<void()>> m_key_pressing_bindings;
            map<const vector<int>, function<void()>> m_key_released_bindings;

            // [keys, click, action] clicking event
            map<const pair<vector<int>, int>, function<void(glm::vec2, glm::vec2)>> m_click_bindings;

            // [keys, click, action] dragging events
            map<const pair<vector<int>, int>, function<void(glm::vec2, glm::vec2, glm::vec2)>> m_drag_bindings;

            // [keys, action] moving events
            map<const vector<int>, function<void(glm::vec2, glm::vec2)>> m_move_bindings;

            // [keys, direction, action] mouse wheel events
            map<const pair<vector<int>, int>, function<void()>> m_wheel_bindings;

        public:
            Controller();
            virtual ~Controller();

            /*!
             * \brief Check all of the keys just released and execute the function associated
             */
            void check();

            // ===== Key binding =====

            /*!
             * \brief Bind a key to a function. Will be checked when key is released
             * \param key the keycode to bind
             * \param action the function that should be executed
             */
            void bindKey(const int key, function<void()> action) {
                vector<int> keys = {key};
                bindKey(keys, KeyState::RELEASED, action);
            };

            /*!
             * \brief Bind a key to a function. Will be checked when key is pressed, being pressed, or released
             * \param key the keycode to bind
             * \param state key state to check
             * \param action the function that should be executed
             */
            void bindKey(const int key, const KeyState state, function<void()> action) {
                vector<int> keys = {key};
                bindKey(keys, state, action);
            };

            /*!
             * \brief Bind a key list to a function. Will be checked when keys are released
             * \param keys keycode list to bind
             * \param action the function that should be executed
             */
            void bindKey(const vector<int> keys, function<void()> action) {
                bindKey(keys, KeyState::RELEASED, action);
            };

            /*!
             * \brief Bind a key list to a function. Will be checked when keys are pressed, being pressed, or released
             * \param keys keycode list to bind
             * \param state keys state to check
             * \param action the function that should be executed
             */
            void bindKey(const vector<int> keys, KeyState state, function<void()> action) {
                switch(state) {
                    case KeyState::PRESSED:
                        m_key_pressed_bindings[keys] = action;
                        break;
                    case KeyState::PRESSING:
                        m_key_pressing_bindings[keys] = action;
                        break;
                    case KeyState::RELEASED:
                        m_key_released_bindings[keys] = action;
                        break;
                }
            }

            // ===== Click binding =====

            /*!
             * \brief Bind a key to a function. Will be checked when key is pressed
             * \param click clickcode to bind
             * \param action the function that should be executed
             */
            void bindClick(const int click, function<void(glm::vec2, glm::vec2)> action) {
                vector<int> temp;
                m_click_bindings[pair<const vector<int>, int>(temp, click)] = action;
            };

            /*!
             * \brief Bind a key to a function. Will be checked when key is pressed
             * \param key the keycode to bind
             * \param click clickcode to bind
             * \param action the function that should be executed
             */
            void bindClick(const int key, const int click, function<void(glm::vec2, glm::vec2)> action) {
                vector<int> temp = {key};
                m_click_bindings[pair<const vector<int>, int>(temp, click)] = action;
            };

            /*!
             * \brief Bind a key to a function. Will be checked when key is pressed
             * \param keys the keycode list to bind
             * \param click clickcode to bind
             * \param action the function that should be executed
             */
            void bindClick(const vector<int> keys, const int click, function<void(glm::vec2, glm::vec2)> action) {
                m_click_bindings[pair<const vector<int>, int>(keys, click)] = action;
            };

            // ===== Drag binding =====

            /*!
             * \brief Bind a key to a function. Will be checked when key is pressed
             * \param click clickcode to bind
             * \param action the function that should be executed
             */
            void bindDrag(const int click, function<void(glm::vec2, glm::vec2, glm::vec2)> action) {
                vector<int> temp;
                m_drag_bindings[pair<const vector<int>, int>(temp, click)] = action;
            };

            /*!
             * \brief Bind a key to a function. Will be checked when key is pressed
             * \param key the keycode to bind
             * \param click clickcode to bind
             * \param action the function that should be executed
             */
            void bindDrag(const int key, const int click, function<void(glm::vec2, glm::vec2, glm::vec2)> action) {
                vector<int> temp = {key};
                m_drag_bindings[pair<const vector<int>, int>(temp, click)] = action;
            };

            /*!
             * \brief Bind a key to a function. Will be checked when key is pressed
             * \param keys the keycode list to bind
             * \param click clickcode to bind
             * \param action the function that should be executed
             */
            void bindDrag(const vector<int> keys, const int click, function<void(glm::vec2, glm::vec2, glm::vec2)> action) {
                m_drag_bindings[pair<const vector<int>, int>(keys, click)] = action;
            };

            // ===== Move binding =====

            /*!
             * \brief Bind simple move event to a function.
             * \param action the function that should be executed
             */
            void bindMove(function<void(glm::vec2, glm::vec2)> action) {
                vector<int> temp;
                m_move_bindings[temp] = action;
            };

            /*!
             * \brief Bind a key and a move to a function. Will be checked when key is pressed
             * \param key the keycode to bind
             * \param action the function that should be executed
             */
            void bindMove(const int key, function<void(glm::vec2, glm::vec2)> action) {
                vector<int> temp = {key};
                m_move_bindings[temp] = action;
            };

            /*!
             * \brief Bind a key list to a function. Will be checked when all the keys are pressed together
             * \param keys the keycode list to bind
             * \param action the function that should be executed
             */
            void bindMove(const vector<int> keys, function<void(glm::vec2, glm::vec2)> action) {
                m_move_bindings[keys] = action;
            };

            // ===== Wheel binding =====

            /*!
             * \brief Bind simple wheel event to a function.
             * \param direction wheeling direction to bind
             * \param action the function that should be executed
             */
            void bindWheel(const int direction, function<void()> action) {
                vector<int> temp;
                m_wheel_bindings[pair<const vector<int>, int>(temp, direction)] = action;
            };

            /*!
             * \brief Bind a key and a direction to a function. Will be checked when key is pressed
             * \param key the keycode to bind
             * \param direction wheeling direction to bind
             * \param action the function that should be executed
             */
            void bindWheel(const int key, const int direction, function<void()> action) {
                vector<int> temp = {key};
                m_wheel_bindings[pair<const vector<int>, int>(temp, direction)] = action;
            };

            /*!
             * \brief Bind a key list to a function. Will be checked when all the keys are pressed together
             * \param keys the keycode list to bind
             * \param direction wheeling direction to bind
             * \param action the function that should be executed
             */
            void bindWheel(const vector<int> keys, const int direction, function<void()> action) {
                m_wheel_bindings[pair<const vector<int>, int>(keys, direction)] = action;
            };

            // ==== Unbinding =====

            /*!
             * \brief Unbind a key, whatever press, pressing or released
             * \param key keycode to unbind
             */
            void unbind(const int key) {
                vector<int> temp = {key};
                m_key_pressed_bindings.erase(temp);
                m_key_pressing_bindings.erase(temp);
                m_key_released_bindings.erase(temp);
            };

            /*!
             * \brief Unbind every keys
             */
            void unbindKeys() {
                m_key_pressed_bindings.clear();
                m_key_pressing_bindings.clear();
                m_key_released_bindings.clear();
            };

            /*!
             * \brief Unbind every click
             */
            void unbindClicks() {
                m_click_bindings.clear();
            };

            /*!
             * \brief Unbind every drag
             */
            void unbindDrags() {
                m_drag_bindings.clear();
            };

            /*!
             * \brief Unbind every move
             */
            void unbindMoves() {
                m_move_bindings.clear();
            };

            // ===== Cursor behavior =====

            static void showCursor(LORE::Window* window) {
                glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            };

            static void hideCursor(LORE::Window* window) {
                glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            };

            static void captureCursor(LORE::Window* window) {
                glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            };

            // ===== Event handling =====

            void listen(LORE::Window* window) {
                glfwSetKeyCallback(window->getWindow(), Controller::keyEvent);
                glfwSetCursorPosCallback(window->getWindow(), Controller::mouseEvent);
                glfwSetScrollCallback(window->getWindow(), Controller::wheelEvent);

                glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }

            static void keyEvent(GLFWwindow* window, const int key, const int scancode, const int state, const int mods) {
                m_key_mutex.lock();
                m_last_key_states[key] = m_key_states[key];
                m_key_states[key] = state;
                m_key_mutex.unlock();
            };

            static void clickEvent(const int key, const int state) {
                m_click_mutex.lock();
                m_last_click_states[key] = m_click_states[key];
                m_click_states[key] = state;
                if(state)
                    m_origin_mouse_pos = m_mouse_pos;
                m_click_mutex.unlock();
            };

            static void mouseEvent(GLFWwindow* window, const double x, const double y) {
                m_mouse_mutex.lock();
                m_last_mouse_pos = m_mouse_pos;
                m_mouse_pos.x = x;
                m_mouse_pos.y = y;
                m_mouse_mutex.unlock();
            };

            static void wheelEvent(GLFWwindow* window, const double dx, const double dy) {
                m_wheel_mutex.lock();
                m_wheel_state = dx;
                m_wheel_mutex.unlock();
            };
    };
}
