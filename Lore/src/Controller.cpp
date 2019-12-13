#include "Controller.h"

using namespace LORE;


std::map<const int, int> Controller::m_key_states;
std::map<const int, int> Controller::m_last_key_states;

std::map<const int, int> Controller::m_click_states;
std::map<const int, int> Controller::m_last_click_states;

int Controller::m_wheel_state;

glm::vec2 Controller::m_mouse_pos;
glm::vec2 Controller::m_last_mouse_pos;
glm::vec2 Controller::m_origin_mouse_pos;

std::mutex Controller::m_key_mutex;
std::mutex Controller::m_mouse_mutex;
std::mutex Controller::m_click_mutex;
std::mutex Controller::m_wheel_mutex;


LORE::Controller::Controller():
    m_key_bindings(),
    m_click_bindings(),
    m_drag_bindings(){}

LORE::Controller::~Controller() {}

void LORE::Controller::check() {
    glm::vec2 diff = m_mouse_pos - m_last_mouse_pos;

    //Simple key release event
    for (const auto p : m_key_bindings) {
        bool success = true;
        for (const auto s : p.first) {
            if (m_last_key_states[s] != 0  || (m_key_states[s] != 1  && m_key_states[s] != 2)) {
                success = false;
                break;
            }
        }
        if (success) p.second();
    }

    //Click + key pressing event
    for (const auto p : m_click_bindings) {
        bool success = true;
        for (const auto s : p.first.first) {
            if (m_key_states[s] != 1) {
                success = false;
                break;
            }
        }
        if (success && (m_last_click_states.find(p.first.second) == m_last_click_states.end()))
            success = false;
        if (success && (m_click_states.find(p.first.second) == m_click_states.end()))
            success = false;
        if (success && m_last_click_states[p.first.second] != 1)
            success = false;
        if (success && m_click_states[p.first.second] != 0)
            success = false;
        if (success && (m_origin_mouse_pos != m_mouse_pos))
            success = false;
        if (success) p.second(m_mouse_pos, diff);
    }

    //Drag + key pressing event
    for (const auto p : m_drag_bindings) {
        bool success = true;
        for (const auto s : p.first.first) {
            if (m_key_states[s] != 1) {
                success = false;
                break;
            }
        }
        if (success && (m_click_states.find(p.first.second) == m_click_states.end()))
            success = false;
        if (success && m_click_states[p.first.second] != 1)
            success = false;
        if (success && diff == glm::vec2(0, 0))
            success = false;
        if (success) p.second(m_origin_mouse_pos, m_mouse_pos, diff);
    }

    //Move + key pressing event
    for (const auto p : m_move_bindings) {
        bool success = true;
        for (const auto s : p.first) {
            if (m_key_states[s] != 1) {
                success = false;
                break;
            }
        }
        if (success && diff == glm::vec2(0, 0))
            success = false;
        if (success) p.second(m_mouse_pos, diff);
    }

    //Wheel event
    for (const auto p : m_wheel_bindings) {
        bool success = true;
        for (const auto s : p.first.first) {
            if (m_key_states[s] != 1) {
                success = false;
                break;
            }
        }
        if (success && m_wheel_state != p.first.second)
            success = false;
        if (success) p.second();
    }

    m_last_click_states = m_click_states;
    m_last_key_states = m_key_states;
    m_last_mouse_pos = m_mouse_pos;
    m_wheel_state = 0;
}
