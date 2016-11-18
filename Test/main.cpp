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


#include <GamePack.h>

#include <OpenGL_Window.h>
#include <Scene.h>
#include <Controller.h>
#include <Camera.h>
#include <FrameBuffer.h>

#include <ObjectManager.h>

using namespace std;
using namespace glm;

int main(int argc, char** argv)
{

	//=================================
	cout << "===== INIT =====" << endl;

	GamePack::init();

	OpenGL_Window* window = GamePack::createWindow("Window_1", "Test");
	Scene* scene = GamePack::createScene("Scene_1", "first");

	OpenGL_Window* w = new OpenGL_Window("test_1", 1600, 900);
	w->init();

    Scene* s_1 = w->getScene();

    Shader* shader = new Shader("default_framebuffer");

    FrameBuffer* f = new FrameBuffer(1600, 900);
    Camera* cam = new Camera(1600, 900, vec3( 2, 2, 2), vec3( 0, 0, 0));
    Scene* s_2 = new Scene();

    f->setCamera(cam);
    cam->setScene(s_2);

    Object* obj = s_1->addObject("plan");
    Object* obj_2 = s_2->addObject("cube_cube");

    shader->load();
    s_2->load();
    f->load();
    w->load();

    obj->getObjects()[0]->getModelRender()->getMaterial()->setShader(shader);
    obj->getObjects()[0]->getModelRender()->getMaterial()->setDiffuseTexture(f->getRenderTexture());
    obj->disablePhysics();

    obj_2->disablePhysics();
    obj_2->setPosition(vec3( 0, 0, 0));

    cam->setProjection(perspective(90.0f, 1600.0f / 900.0f, 0.1f, 500.0f));

    //----------

	Controller* c = new Controller();

	//===================================
	cout << "===== RENDER =====" << endl;

	c->setMouseEvent([&cam](double x, double y, double dx, double dy) {

        cam->orienter(dx, dy);});
	/*c->bind(GLFW_KEY_P, [&s](double x, double y) {

		cout << "test_0" << endl;

        Object* obj = ObjectManager::get("cube_cube");
		obj->load();
		//obj->setPosition(vec3(0, 20, 0));
		//s->addRigidBody(obj->getModelBullet());

		s->addObject(obj);});*/
	c->bind(GLFW_KEY_W, [&cam](double x, double y) {

		cout << "test_1" << endl;

        cam->deplacer(vec3(0.2, 0.2, 0.2));});
	c->bind(GLFW_KEY_S, [&cam](double x, double y) {

		cout << "test_1" << endl;

        cam->deplacer(vec3(-0.2, -0.2, -0.2));});
	c->bind(GLFW_KEY_A, [&cam](double x, double y) {

		cout << "test_2" << endl;

        cam->deplacer();});
	c->bind(GLFW_KEY_D, [&cam](double x, double y) {

		cout << "test_3" << endl;

        cam->deplacer();});
	c->bind(GLFW_KEY_SPACE, [&cam](double x, double y) {

		cout << "test_4" << endl;});

	//c->toggleCaptureCursor();
	//c->toggleVisibleCursor();

	while (!w->shouldClose())
	{

		int start = w->startFrame();

		c->check(w);

		s_2->step();

		f->render();
		w->render();
		//cam->render();

		w->endFrame(start);

	}

	//================================
	cout << "===== END =====" << endl;

	delete f;
	delete s_2;
	delete w;
	delete c;

	GamePack::unload();

	exit(0);
    return 0;

}

