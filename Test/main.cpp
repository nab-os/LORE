#include <iostream>
#include <string>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Lore.h>
#include <Cube.h>

using namespace std;
using namespace glm;
using namespace LORE;

int main(int argc, char** argv)
{

    cout << "===== INIT =====" << endl;

    LORE::Window* window = LORE::Lore::init(); // Initializes OpenGL context and creates a Window
    if(!window)
    {
        cout << "Error during OpenGL context initialization." << endl;
        Lore::unload();
        return -1;
    }

    string file = "./Objects/TriangleWithoutIndices.gltf";

    if(argc >= 2)
    {

        file = argv[1];

    }

    Scene* default_scene = Lore::load(file);
    cout << "Scene_ " << default_scene << endl;
    //cout << "Test: " << Lore::getScene("Scene") << endl;
    //cout << "Test: " << Lore::getNode("Camera") << endl;
    //cout << "Test: " << Lore::getNode("Cube") << endl;
    window->getCamera()->setScene(default_scene);

    //----------

    Controller* controller = new Controller(); // a Controller to bind the ESCAPE key to the Window

    controller->bind(GLFW_KEY_ESCAPE, [&window](double x, double y) {

        window->close();

    });
    
    controller->bind(GLFW_KEY_W, [&window](double x, double y) {
        window->getCamera()->forward();
    });
    controller->bind(GLFW_KEY_S, [&window](double x, double y) {
        window->getCamera()->backward();
    });
    controller->bind(GLFW_KEY_A, [&window](double x, double y) {
        window->getCamera()->left();
    });
    controller->bind(GLFW_KEY_D, [&window](double x, double y) {
        window->getCamera()->right();
    });
    controller->bind(GLFW_KEY_SPACE, [&window](double x, double y) {
        window->getCamera()->up();
    });
    controller->bind(GLFW_KEY_LEFT_SHIFT, [&window](double x, double y) {
        window->getCamera()->down();
    });

    controller->setMouseEvent([&window](double x, double y, double dx, double dy){
        window->getCamera()->orienter(dx, dy);
    });


    //===================================
    cout << "===== RENDER =====" << endl;

    while (!window->shouldClose())
    {

        int start = window->startFrame(); // Begin the frame render process

        controller->check(window); // Checks all bindings for the Window and execute the fonction if it matches

        window->render(); //

        window->endFrame(start); // End the frame render process and display the image on the window

    }

    //================================
    cout << "===== END =====" << endl;

    delete controller;

    Lore::unload(); // Unload all dictionnaries, and unload OpenGL context

    cout << "===== SUCCESSFULLY ENDED =====" << endl;
    return 0;

}
