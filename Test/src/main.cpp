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

using std::cout;
using std::endl;
using std::string;
using glm::vec3;
using glm::quat;

using namespace LORE;

int main(int argc, char** argv) {
    cout << "===== INIT =====" << endl;

    Window* window = Lore::init(); // Initializes OpenGL context and creates a Window
    if(!window) {
        cout << "Error during OpenGL context initialization." << endl;
        Lore::unload();
        return -1;
    }

    string file = "./Objects/empty.gltf";
    if(argc >= 2) {
        file = argv[1];
    }

    cout << "===Importing===" << endl;
    Scene* default_scene = Lore::load(file);
    cout << "===Finished importing===" << endl;
    cout << "Scene_ " << default_scene << endl;
    Camera* camera = Lore::getCamera("Camera");
    if(!camera) {
        cout << "Could'nt find Camera, creating one..." << endl;
        camera = Lore::createCamera("Camera");
        camera->setPosition(vec3(5, 5, 5));
        camera->setScene(default_scene);
    }
	camera = Lore::createCamera("Camera");
	camera->setPosition(vec3(5, 5, 5));
	camera->setScene(default_scene);
    window->setCamera(camera);

    Lore::listCameras();

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

    controller->bindKey(GLFW_KEY_ESCAPE, [&window]() {
        window->close();
    });

    controller->bindKey(GLFW_KEY_W, LORE::KeyState::PRESSING, [&window]() {
        window->getCamera()->forward();
    });
    controller->bindKey(GLFW_KEY_S, LORE::KeyState::PRESSING, [&window]() {
        window->getCamera()->backward();
    });
    controller->bindKey(GLFW_KEY_A, LORE::KeyState::PRESSING, [&window]() {
        window->getCamera()->left();
    });
    controller->bindKey(GLFW_KEY_D, LORE::KeyState::PRESSING, [&window]() {
        window->getCamera()->right();
    });
    controller->bindKey(GLFW_KEY_SPACE, LORE::KeyState::PRESSING, [&window]() {
        window->getCamera()->up();
    });
    controller->bindKey(GLFW_KEY_LEFT_SHIFT, LORE::KeyState::PRESSING, [&window]() {
        window->getCamera()->down();
    });

    controller->bindMove([&window](auto origin, auto offset){
        window->getCamera()->setOrientation(offset.x, offset.y);
    });

	controller->bindKey(GLFW_KEY_T, [&window]() {
		window->setCamera(Lore::getCamera("Camera"));
    });

	controller->bindKey(GLFW_KEY_G, [&window]() {
		window->setCamera(Lore::getCamera("Camera_1"));
    });

    controller->listen(window);

    float a = 0;

    //===================================
    cout << "===== RENDER =====" << endl;
    while (!window->shouldClose()) {
        int start = window->startFrame(); // Begin the frame render process

        controller->check(); // Checks all bindings for the Window and execute the fonction if it matches
        cameraPos = camera->getPosition();
        a += 0.01;
        Light::lightPosition = vec3(sin(a)*6, 3, cos(a)*6);
        //obj->setPosition(Light::lightPosition);
        quat myQuat = quat(vec3(0,-a,0));
        obj->setRotation(myQuat);

        window->render(); //
        window->endFrame(start); // End the frame render process and display the image on the window
    }

    //================================
    cout << "===== END =====" << endl;

    delete controller;
    delete diamond;

    Lore::unload(); // Unload all dictionnaries, and unload OpenGL context

    cout << "===== SUCCESSFULLY ENDED =====" << endl;
    return 0;
}
