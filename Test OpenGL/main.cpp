// Test OpenGL.cpp : définit le point d'entrée pour l'application console.
//

#include <stdio.h>
#include <iostream>
#include <string>

#include <btBulletDynamicsCommon.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <OpenGL_Window.h>
#include <Scene.h>
#include <Controller.h>

using namespace std;

int main()
{

	//=================================
	cout << "===== INIT =====" << endl;

	OpenGL_Window* w = new OpenGL_Window("test_1", 1600, 900);
	w->init();

	Scene* s = w->getScene();
	Object* obj = s->addObject("cube_cube");
	s->load();

	//----------

	Controller* c = new Controller();

	//===================================
	cout << "===== RENDER =====" << endl;

	double a = 0;
	int b = 1;

	glm::vec3 pos = glm::vec3(0, 0, 0);
	c->bind(GLFW_KEY_Q, [&a]() {

		cout << "test_1" << endl;
		a += 0.1;

	});
	c->bind(GLFW_KEY_D, [&a]() {

		cout << "test_2" << endl;
		a -= 0.1;

	});

	while (!w->shouldClose())
	{

		//a += 0.1 * b;
		//b = a > 3.14 ? -1 : b;
		//b = a <= 0 ? 1 : b;

		/*
		pos.x = sin(a);
		pos.z = cos(a);

		obj->setPosition(pos);
		*/
		int start = w->startFrame();

		c->check(w);

		w->step();
		w->render();

		w->endFrame(start);

	}

	//================================
	cout << "===== END =====" << endl;

	delete w;
	delete c;

	exit(0);
    return 0;

}

