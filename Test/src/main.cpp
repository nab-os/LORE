#include <iostream>
#include <string>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include <Lore.h>
#include <Light.h>
#include <Cube.h>

#include "Diamond.h"

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

    string file = "./Objects/empty.gltf";
    if(argc >= 2)
    {
        file = argv[1];
    }
    Camera* camera = new Camera();
    camera->setPosition(vec3(5, 5, 5));
    window->setCamera(camera);
    

    Scene* default_scene = Lore::load(file);
    cout << "Scene_ " << default_scene << endl;
    camera->setScene(default_scene);
    camera->setPointcible(vec3(1.0));

    Material* mat_reflections = Lore::createMaterial("reflections");
    mat_reflections->load();
    Shader* shader_reflections = Lore::createShader("reflections");
    shader_reflections->load();
    mat_reflections->setShader(shader_reflections);
    mat_reflections->setCulling(false);

    Diamond* diamond = new Diamond();
    diamond->load();
    diamond->setMaterial(mat_reflections);

    Object* obj = Lore::createObject("cube");
    obj->setMesh(diamond);
    default_scene->addChild(obj);

    vec3 cameraPos;
    mat_reflections->addCustomVec3Uniform("cameraPos", &cameraPos);


    //----------

    Controller* controller = new Controller(); // a Controller to bind the ESCAPE key to the Window

    controller->bind(GLFW_KEY_ESCAPE, [&window](double x, double y) {
        window->close();
    });
    
    controller->bind(GLFW_KEY_W, [&camera](double x, double y) {
        camera->forward();
    });
    controller->bind(GLFW_KEY_S, [&camera](double x, double y) {
        camera->backward();
    });
    controller->bind(GLFW_KEY_A, [&camera](double x, double y) {
        camera->left();
    });
    controller->bind(GLFW_KEY_D, [&camera](double x, double y) {
        camera->right();
    });
    controller->bind(GLFW_KEY_SPACE, [&camera](double x, double y) {
        camera->up();
    });
    controller->bind(GLFW_KEY_LEFT_SHIFT, [&camera](double x, double y) {
        camera->down();
    });

    controller->setMouseEvent([&camera](double x, double y, double dx, double dy){
        camera->orienter(dx, dy);
    });

    float a = 0;

    //===================================
    cout << "===== RENDER =====" << endl;

    while (!window->shouldClose())
    {
        int start = window->startFrame(); // Begin the frame render process

        controller->check(window); // Checks all bindings for the Window and execute the fonction if it matches
        cameraPos = camera->getPosition();
        a += 0.01;
        Light::lightPosition = vec3(sin(a)*6, 3, cos(a)*6);
        //obj->setPosition(Light::lightPosition);
        quat myQuat = quat(vec3(0,a,0));
        obj->setRotation(myQuat);

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
