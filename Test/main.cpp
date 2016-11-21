#include <iostream>
#include <GamePack.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>

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

    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile("simple.dae", aiProcess_Triangulate);


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
