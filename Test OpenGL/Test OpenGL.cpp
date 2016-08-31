// Test OpenGL.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
#include <string>

#include <Window.h>
#include <Scene.h>


using namespace std;

int main()
{

	Window* w = new Window("", 1600, 900);
	w->init();

	Scene* s = w->addScene("scene");

	Object* obj = s->addObject();

	s->load();
	
	while (!w->shouldClose())
	{
	
		int start = w->startFrame();

		s->render();

		w->endFrame(start);

	}

    return 0;

}

