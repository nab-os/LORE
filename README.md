# GamePack | STILL IN DEVELOPMENT /!\

Light 3D library based on OpenGL that allows you to create/import 3D environment.
You can create games, use it to visualize raw data, etc...

##Exemple

```C++
//Wait for it
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
