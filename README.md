# Lore | STILL IN DEVELOPMENT /!\

Light 3D library based on OpenGL that allows you to create/import 3D environment.
You can create games, use it to visualize raw data, etc...

##Exemple

A simple window that closes when ESCAPE key is pressed

```C++
#include <iostream>
#include <Lore.h>

using namespace std;
int main(int argc, char** argv)
{

	cout << "===== INIT =====" << endl;

	OpenGL_Window* window = Lore::init(); // Initializes OpenGL context and creates a Window
	if(!window)
	{
		cout << "Error during OpenGL context initialization." << endl;
		Lore::unload();
		return -1;
	}

    //----------

	Controller* controller = new Controller(); // a Controller to bind the ESCAPE key to the Window

	controller->bind(GLFW_KEY_ESCAPE, [&window](double x, double y) {

		window->close();

    });

	//===================================
	cout << "===== RENDER =====" << endl;

	while (!window->shouldClose())
	{

		int start = window->startFrame(); // Begin the frame render process

		controller->check(window); // Checks all bindings for the Window and execute de fonction if it matches

		window->render(); //

		window->endFrame(start); // End the frame render process and display the image on the window

	}

	//================================
	cout << "===== END =====" << endl;

	Lore::unload(); // Unload all dictionnaries, and unload OpenGL context

    return 0;

}
```
## Why ?

The purpose of this project is to create a simple and lightweight tool to use all the OpenGL's power.
Another aim of this project is to stay cross-platform and open.

## Installation

Clone the project
```bash
git clone https://github.com/gnikwo/Lore
```

and install gcc if it's not done yet
```bash
apt install gcc
```

### Dependencies 

You will need to install multiple libraries :

* -glew: OpenGL development environment
* -glm: Math objects for OpenGL
* -glfw3: Window and context handler
* -soil: Texture loading library
* -bullet physics: Physics library
* -open collada: collada document importer

```bash
apt install libglew-dev libglm-dev libsoil-dev libglfw3-dev libbullet-dev opencollada-dev
```

## Licence

Copyright (C) 2016 Nicolas Ballet

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the
Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
Boston, MA  02110-1301, USA.
