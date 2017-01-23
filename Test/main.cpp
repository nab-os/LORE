#include <iostream>
#include <string>

#include <Lore.h>

using namespace std;
using namespace LORE;
int main(int argc, char** argv)
{

    cout << "===== INIT =====" << endl;

    LORE::Window* window = LORE::Lore::init(); // Initializes OpenGL context and creates a Window
    /*if(!window)
    {
        cout << "Error during OpenGL context initialization." << endl;
        Lore::unload();
        return -1;
    }

    string file = "/home/guy/Bureau/simple.dae";

    if(argc >= 2)
    {

        file = argv[1];

    }

    Lore::load(file);

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
*/
    return 0;

}
