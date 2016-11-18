# GamePack | STILL IN DEVELOPMENT /!\

Light 3D library based on OpenGL that allows you to create/import 3D environment.
You can create games, use it to visualize raw data, etc...

##Exemple

A simple window that closes when ESCAPE key is pressed

```C++
#include <iostream>
#include <GamePack.h>

using namespace std;
int main(int argc, char** argv)
{

	cout << "===== INIT =====" << endl;

	OpenGL_Window* window = GamePack::init(); // Initializes OpenGL context and creates a Window
	if(!window)
	{
		cout << "Error during OpenGL context initialization." << endl;
		GamePack::unload();
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

	GamePack::unload(); // Unload all dictionnaries, and unload OpenGL context

    return 0;

}
```
## Why ?

The purpose of this project is to create a simple and lightweight tool to use all the OpenGL's power.
Another aim of this project is to stay cross-platform and open.

## Installation

Clone the project
```bash
git clone https://github.com/gnikwo/GamePack
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

```bash
apt install libglew-dev glew-utils libglfw3 libglfw3-dev libglm-dev libbullet-dev
```

## Licence

MIT License

Copyright © 2016 Nicolas Ballet

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
